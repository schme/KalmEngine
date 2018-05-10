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

#include "Shader.cpp"
#include "Sys_Config.h"

#if KALM_INTERNAL
#include "_stb/stb_easy_font.h"
#endif

static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);
static void FramebufferResizeCallback( GLFWwindow *window, const i32 width, const i32 height);


const u32 VERTEX_ARRAYS = 3;
const u32 VERTEX_BUFFERS = 5;
const u32 ELEMENT_BUFFERS = VERTEX_BUFFERS;
const u32 SHADER_PROGRAMS = 5;
const u32 TEXTURES = 1;

static u32 VertexArrays[VERTEX_ARRAYS];
static u32 VertexBuffers[VERTEX_BUFFERS];
static u32 ElementBuffers[ELEMENT_BUFFERS];
static u32 ShaderPrograms[SHADER_PROGRAMS];
static u32 Textures[TEXTURES];
static Shader shaders[SHADER_PROGRAMS];

b32 drawWireframe = false;

/** TODO(Kasper): Figure out how best to do multiple shaders */
static u32 currentSceneID = 0;

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

    mat4 p = GetPerspectiveMat( 60.0f, (f32)frameBufferWidth / (f32)frameBufferHeight, 0.1f, 100.0f);

    /** shader */
    kShaderLoader shaderLoader;
    shaderLoader.LoadShader( &(shaders[0]), through_vert, through_frag);
    shaders[0].Use();
    shaders[0].SetMat4( "projection", p);

    shaderLoader.LoadShader( &(shaders[1]), through_vert, light_frag);
    shaders[1].Use();
    shaders[1].SetMat4( "projection", p);

    /** debug info shader */
    shaderLoader.LoadShader( &(shaders[2]), debug_vert, debug_frag);

    /** Dragons */

    MeshComponent* meshComp = (MeshComponent*)scene->children[0]->components[0];
    kMesh_t *mesh = meshComp->mesh;

    renderType_t type;
    type.vertexArrayIndex = 0;
    type.vertexBufferIndex = 0;
    type.shaderIndex = 0;

    this->LoadVertices( mesh, &type);
    std::memcpy( (void*)(&renderGroups[0]), &type, sizeof( type ));


    /** D20 */

    MeshComponent* d20MeshComp = (MeshComponent*)scene->children[1]->components[0];
    kMesh_t *d20Mesh = d20MeshComp->mesh;

    renderType_t d20Type;
    d20Type.vertexArrayIndex = 1;
    d20Type.vertexBufferIndex = 1;
    d20Type.shaderIndex = 0;

    this->LoadVertices( d20Mesh, &d20Type);
    std::memcpy( (void*)(&(renderGroups[1])), &d20Type, sizeof( d20Type ));


    /** Lights */

    MeshComponent* lightCubeMeshComp = (MeshComponent*)scene->children[2]->components[0];
    kMesh_t *lightCubeMesh = lightCubeMeshComp->mesh;

    renderType_t lightCubeType;
    lightCubeType.vertexArrayIndex = 2;
    lightCubeType.vertexBufferIndex = 2;
    lightCubeType.shaderIndex = 1;

    this->LoadVertices( lightCubeMesh, &lightCubeType);
    std::memcpy( (void*)(&(renderGroups[2])), &lightCubeType, sizeof( lightCubeType ));
}


void kRender::LoadVertices( const kMesh_t *mesh, const renderType_t *type) const {

    u32 bytesPerVertice = (3 + (3 * mesh->hasNormals) + (2 * mesh->hasTexcoords) + (4 * mesh->hasColors)) * sizeof(f32);

    glBindVertexArray( VertexArrays[ type->vertexArrayIndex ]);

    glBindBuffer( GL_ARRAY_BUFFER, VertexBuffers[ type->vertexBufferIndex ]);
    glBufferData( GL_ARRAY_BUFFER, mesh->vertices_n * bytesPerVertice, mesh->vertices, GL_STATIC_DRAW);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ElementBuffers[ type->vertexBufferIndex ]);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, mesh->indices_n * sizeof( u32), mesh->indices, GL_STATIC_DRAW);

    /* f32[3] position, f32[3] normal, f32[2] texCoord */
    const u32 stride = (3 * mesh->hasVertices + 3 * mesh->hasNormals + 2 * mesh->hasTexcoords + 4 * mesh->hasColors ) * sizeof(f32);

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
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, stride, (void*)((3 + 3 * mesh->hasNormals) * sizeof(f32)));
        glEnableVertexAttribArray(2);
    }

    if( mesh->hasColors) {
        /* color */
        glVertexAttribPointer( 3, 4, GL_FLOAT, GL_FALSE, stride, (void*)((3 + 3 * mesh->hasNormals + 2 * mesh->hasTexcoords) * sizeof(f32)));
        glEnableVertexAttribArray(3);
    }

}

/*
 * When making modelView matrix:
 * 1) Transpose view
 * 2) Translate objects, Transpose result
 * 3) Scale
 * 4) RotationX() * model
 * 5) model * view TODO(Kasper): Would changing order to view * model get rid of transposes?
 */
void kRender::DrawTestScene( kScene_t *scene) const {

    CheckToggleWireframe();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    kCamera *camera = scene->camera;

    mat4 view = LookAt( camera->position, camera->position + camera->front, camera->right, camera->up );
    view = Transpose(view);

    /* dragons */
    DrawObject_r( scene->children[0], GetIdentityMat(), Vec3( 0.0f, 0.0f, 0.0f), view, &renderGroups[0] );
    DrawObject_r( scene->children[1], GetIdentityMat(), Vec3( 0.0f, 0.0f, 0.0f), view, &renderGroups[1] );
    DrawObject_r( scene->children[2], GetIdentityMat(), Vec3( 0.0f, 0.0f, 0.0f), view, &renderGroups[2] );

    glfwSwapBuffers((GLFWwindow*)window);
}

/**
 * rotation should be in degrees
 */
void kRender::DrawObject_r( const kObject *obj, const mat4 parentModelView, const vec3 rotation, const mat4 view, const renderType_t *rndGroup) const {

    glBindVertexArray( VertexArrays[ rndGroup->vertexArrayIndex]);

    mat4 model = GetIdentityMat();

    /** the order of translate and scale does not seem to matter */
    model = Transpose(Translate( model, obj->position ));

    model = Scale( model, Vec3( obj->scale));

    model = RotationX( Radians(rotation.x)) * RotationY( Radians(rotation.y)) * RotationZ( Radians(rotation.z)) * model;

    mat4 modelViewMatrix = model * view;

    /** This also runs Use() on the shader object */
    SetModelViewMatrix( rndGroup->shaderIndex, modelViewMatrix);
    glDrawElements( GL_TRIANGLES, ((MeshComponent*)obj->components[0])->mesh->indices_n, GL_UNSIGNED_INT, 0);

    for( u32 i = 0; i < obj->children_n; i++) {
        DrawObject_r( obj->children[i], modelViewMatrix, Vec3(0.0f), view, rndGroup);
    }
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

/** TODO(Kasper): Support multiple shaders */
void kRender::SetMatrixUniform( const u32 shaderID, const char *name, mat4 matrix) const {
    shaders[shaderID].Use();
    shaders[shaderID].SetMat4( name, matrix );
}

void kRender::SetModelViewMatrix( const u32 shaderID, const mat4 modelView ) const {
    shaders[shaderID].Use();
    shaders[shaderID].SetMat4( "modelView", modelView );
}

void kRender::SetProjectionMatrix( const u32 shaderID, const mat4 projection ) const {
    projectionMatrix = projection;
    shaders[shaderID].Use();
    shaders[shaderID].SetMat4( "projection", projection);
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
    glViewport(0, 0, width, height);
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

void kRender::CheckToggleWireframe() const {
    if( g_Config->GetPreferences()->drawWireframe == drawWireframe) {
        return;
    }

    /* we switched drawWireframe on */
    if( !drawWireframe ) {
        drawWireframe = true;
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    } else {
        drawWireframe = false;
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    }
}
