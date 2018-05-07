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

static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);
static void FramebufferResizeCallback( GLFWwindow *window, const i32 width, const i32 height);


const u32 VERTEX_ARRAYS = 1;
const u32 VERTEX_BUFFERS = 1;
const u32 ELEMENT_BUFFERS = VERTEX_BUFFERS;
const u32 SHADER_PROGRAMS = 1;
const u32 TEXTURES = 1;

static u32 VertexArrays[VERTEX_ARRAYS];
static u32 VertexBuffers[VERTEX_BUFFERS];
static u32 ElementBuffers[ELEMENT_BUFFERS];
static u32 ShaderPrograms[SHADER_PROGRAMS];
static u32 Textures[TEXTURES];

static renderBufferGroup_t *currentGroup = nullptr;
static u32 currentSceneID = 0;

static mat4 perspectiveMatrix = {};

void kRender::LoadTexture( kTexture_t* text) {

    glBindTexture( GL_TEXTURE_2D, Textures[text->ID]);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, text->image->width, text->image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, text->image->imageBuffer);
    glGenerateMipmap( GL_TEXTURE_2D);
}


void kRender::LoadVertices( kMesh_t *verts, const u32 buffer_id) const {

    glBindVertexArray( VertexArrays[ 0 ]);

    glBindBuffer( GL_ARRAY_BUFFER, VertexBuffers[ buffer_id ]);
    glBufferData( GL_ARRAY_BUFFER, verts->vertices_n * sizeof( f32), verts->vertices, GL_STATIC_DRAW);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ElementBuffers[ buffer_id ]);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, verts->indices_n * sizeof( u32), verts->indices, GL_STATIC_DRAW);

    /* f32[3] position, f32[3] normal, f32[2] texCoord */
    const u32 stride = (3 + 3 + 2) * sizeof(f32);

    /* position */
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    /* normal */
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    /* texcoord */
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(f32)));
    glEnableVertexAttribArray(2);

}


void kRender::Draw() const {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);


    //glDrawElements();
    glfwSwapBuffers((GLFWwindow*)window);
}


void kRender::SetWindow( GLFWwindow * new_window ) {
    this->window = new_window;
}

void kRender::Initialize() {

    glClearColor( 0.05f, 0.05f, 0.05f, 1.0f);
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


/**
 * Changes infrequently
 */
void kRender::SetPerspectiveMatrix( mat4 perspective ) {
    perspectiveMatrix = perspective;
}

void kRender::SetGroupModelView( mat4 modelView ) {
    currentGroup->shader.Use();
    currentGroup->modelView = modelView;
    s32 modelViewLoc = glGetUniformLocation( currentGroup->shader.ID, "modelView");
    glUniformMatrix4fv( modelViewLoc, 1, GL_FALSE, (f32*)currentGroup->modelView.A);
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

void kRender::PrintOpenGLShaderError( u32 shader, const char *message) const {
    char infoLog[512];
    glGetShaderInfoLog( shader, 512, NULL, infoLog);
    PRINTL_STR(message);
    PRINTL_STR( infoLog);
}
