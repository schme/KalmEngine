/**
 *
 * Render.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Types.h"
#include "Sys_Render.h"
#include "Sys_Shared.h"
#include "KalmShared.h"

#include "Shader.cpp"

static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);
static void FramebufferResizeCallback( GLFWwindow *window, const i32 width, const i32 height);


const u32 VERTEX_ARRAYS = 1;
const u32 VERTEX_BUFFERS = 5;
const u32 ELEMENT_BUFFERS = VERTEX_BUFFERS;
const u32 SHADER_PROGRAMS = 1;
const u32 TEXTURES = 1;

static u32 VertexArrays[VERTEX_ARRAYS];
static u32 VertexBuffers[VERTEX_BUFFERS];
static u32 ElementBuffers[ELEMENT_BUFFERS];
static u32 ShaderPrograms[SHADER_PROGRAMS];
static u32 Textures[TEXTURES];

/** TODO(Kasper): Figure out how best to do multiple shaders */
static Shader shader = {};
static u32 currentSceneID = 0;

static kMesh_t *currentMesh = nullptr;
static mat4 projectionMatrix = {};

void kRender::LoadTexture( kTexture_t* text) {

    glBindTexture( GL_TEXTURE_2D, Textures[text->ID]);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, text->image->width, text->image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, text->image->imageBuffer);
    glGenerateMipmap( GL_TEXTURE_2D);
}


/**
 * TODO(Kasper): Extremely unsafe and specific
 */
void kRender::LoadTestScene( kScene_t *scene ) const {

    /** shader */
    kShaderLoader shaderLoader;
    shaderLoader.LoadShader( &shader, through_vert, through_frag);

    MeshComponent* meshComp = (MeshComponent*)scene->objects[0]->components[0];
    kMesh_t *mesh = meshComp->mesh;
    currentMesh = mesh;

    mat4 p = GetPerspectiveMat( 60.0f, (f32)frameBufferWidth / (f32)frameBufferHeight, 0.1f, 100.0f);

    SetProjectionMatrix( p);

    this->LoadVertices( currentMesh, 0);

}

void kRender::LoadVertices( kMesh_t *mesh, const u32 buffer_id) const {

    u32 bytesPerVertice = (3 + (3 * mesh->hasNormals) + (2 * mesh->hasTexcoords)) * sizeof(f32);

    glBindVertexArray( VertexArrays[ 0 ]);

    glBindBuffer( GL_ARRAY_BUFFER, VertexBuffers[ buffer_id ]);
    glBufferData( GL_ARRAY_BUFFER, mesh->vertices_n * bytesPerVertice, mesh->vertices, GL_STATIC_DRAW);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ElementBuffers[ buffer_id ]);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, mesh->indices_n * sizeof( u32), mesh->indices, GL_STATIC_DRAW);

    /* f32[3] position, f32[3] normal, f32[2] texCoord */
    const u32 stride = (3 * mesh->hasVertices + 3 * mesh->hasNormals + 2 * mesh->hasTexcoords) * sizeof(f32);

    /* position */
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    if( mesh->hasNormals) {
        /* normal */
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(f32)));
        glEnableVertexAttribArray(1);
    }

    if( mesh->hasTexcoords) {
        /* texcoord */
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(f32)));
        glEnableVertexAttribArray(2);
    }

}

void kRender::DrawTestScene( kScene_t *scene) const {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

    shader.Use();
    kCamera *camera = scene->camera;
    mat4 view = LookAt( camera->position, camera->front, camera->right, camera->up );

    for( int i=0; i < 5; ++i) {

        mat4 model = GetIdentityMat();

        model = Transpose(Translate( model, scene->objects[i]->position ));
        //model = model * (RotationX( Radians(angle) ) * RotationY( Radians(angle) *0.3f) * RotationZ( Radians(angle)*0.5f));

        model = Scale( model, Vec3(20.0f));

        f32 angle = 20.0f * i;
        model = model * RotationX( Radians(angle)) * RotationY( Radians(angle) * 0.3f) * RotationZ( Radians( angle ) * 0.5f);

        mat4 modelViewMatrix = model * view;
        SetModelViewMatrix( modelViewMatrix);

        glDrawElements( GL_TRIANGLES, currentMesh->indices_n, GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers((GLFWwindow*)window);
}


void kRender::Draw() const {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapBuffers((GLFWwindow*)window);
}


void kRender::SetWindow( GLFWwindow * new_window ) {
    this->window = new_window;
}

void kRender::Initialize() {

    glClearColor( 0.10f, 0.10f, 0.10f, 1.0f);
    glEnable( GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback( kRender::window, FramebufferResizeCallback);
    glfwSetWindowSizeCallback( kRender::window, ResizeCallback);

    i32 width, height;
    glfwGetFramebufferSize( kRender::window, &width, &height);
    glViewport(0, 0, width, height);

    glGenVertexArrays( VERTEX_ARRAYS, VertexArrays);
    glGenBuffers( VERTEX_BUFFERS, VertexBuffers);
    glGenBuffers( ELEMENT_BUFFERS, ElementBuffers);
    glGenTextures( TEXTURES, Textures);
}

void kRender::SetMatrixUniform( const char *name, mat4 matrix) const {
    shader.Use();
    shader.SetMat4( name, matrix );
}

void kRender::SetModelViewMatrix( mat4 modelView ) const {
    shader.Use();
    shader.SetMat4( "modelView", modelView );
}


/**
 * Changes infrequently
 * TODO(Kasper): Constify
 */
void kRender::SetProjectionMatrix( mat4 projection ) const {
    projectionMatrix = projection;
    shader.Use();
    shader.SetMat4( "projection", projection);
}


/**
 * GENERAL
 */

void ResizeCallback( GLFWwindow* wnd, const i32 numer, const i32 denom) {
    i32 width, height;
    glfwGetFramebufferSize( wnd, &width, &height);
    glfwSetWindowSize( wnd, width, height);
}

void FramebufferResizeCallback( GLFWwindow* wnd, const i32 width, const i32 height) {
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}


void kRender::PrintOpenGLProgramError( u32 program, const char *message) const {
    char infoLog[512];
    glGetProgramInfoLog( program, 512, NULL, infoLog);
    PRINTL_STR(message);
    PRINTL_STR( infoLog);
}

void kRender::PrintOpenGLShaderError( u32 shaderID, const char *message) const {
    char infoLog[512];
    glGetShaderInfoLog( shaderID, 512, NULL, infoLog);
    PRINTL_STR(message);
    PRINTL_STR( infoLog);
}
