/**
 *
 * Render.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Types.h"
#include "Render.h"
#include "SystemsLocal.h"

#include "Shader.cpp"

const u32 VERTEX_ARRAYS = 1;
const u32 VERTEX_BUFFERS = 1;
const u32 ELEMENT_BUFFERS = VERTEX_BUFFERS;
const u32 SHADER_PROGRAMS = 1;

static u32 VertexArrays[VERTEX_ARRAYS];
static u32 VertexBuffers[VERTEX_BUFFERS];
static u32 ElementBuffers[ELEMENT_BUFFERS];
static u32 ShaderPrograms[SHADER_PROGRAMS];

static renderBufferGroup_t *currentGroup = nullptr;
static u32 currentSceneID = 0;

static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);
static void FramebufferResizeCallback( GLFWwindow *window, const i32 width, const i32 height);

static mat4 perspectiveMatrix = {};

void kRender::LoadScene( kScene_t *scene) {

    currentSceneID = scene->ID;
    renderBufferGroup_t *group = g_Assets->GetBufferGroup();
    currentGroup = group;

    currentGroup->shader.Use();
    s32 perspectiveLoc = glGetUniformLocation( currentGroup->shader.ID, "perspective");
    glUniformMatrix4fv( perspectiveLoc, 1, GL_FALSE, (f32*)perspectiveMatrix.A);

    glBindVertexArray( VertexArrays[ scene->ID ] );

    glBindBuffer( GL_ARRAY_BUFFER, VertexBuffers[ group->ID]);
    glBufferData( GL_ARRAY_BUFFER, group->elements->vertices_n * sizeof(f32), group->elements->vertices, GL_STATIC_DRAW);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ElementBuffers[ group->ID]);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, group->elements->indices_n * sizeof(u32), group->elements->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

void kRender::RenderCurrentScene() const {
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    
    currentGroup->shader.Use();
    glDrawElements( GL_TRIANGLES, currentGroup->elements->indices_n, GL_UNSIGNED_INT, 0);
}

void kRender::Initialize() {

    glClearColor( 0.1f, 0.1f, 0.1f, 1.0f);
    glEnable( GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback( kRender::window, FramebufferResizeCallback);
    glfwSetWindowSizeCallback( kRender::window, ResizeCallback);

    i32 width, height;
    glfwGetFramebufferSize( kRender::window, &width, &height);
    glViewport(0, 0, width, height);

    glGenVertexArrays( VERTEX_ARRAYS, VertexArrays);
    glGenBuffers( VERTEX_BUFFERS, VertexBuffers);
    glGenBuffers( ELEMENT_BUFFERS, ElementBuffers);
}


void kRender::SetWindow( GLFWwindow * new_window ) {
    this->window = new_window;
}

void kRender::Draw() const {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderCurrentScene();

    glfwSwapBuffers((GLFWwindow*)window);
    glfwPollEvents();   //TODO(Kasper): Where is this supposed to be?
}

void kRender::SetPerspective( mat4 perspective ) {
    perspectiveMatrix = perspective;
}

void kRender::SetGroupModelView( mat4 modelView ) {
    currentGroup->shader.Use();
    currentGroup->modelView = modelView;
    s32 modelViewLoc = glGetUniformLocation( currentGroup->shader.ID, "modelView");
    glUniformMatrix4fv( modelViewLoc, 1, GL_FALSE, (f32*)currentGroup->modelView.A);
}


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
