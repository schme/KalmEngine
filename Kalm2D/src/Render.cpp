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
#include "Shader.h"

const u32 VERTEX_ARRAYS = 1;
const u32 VERTEX_BUFFERS = 1;
const u32 SHADER_PROGRAMS = 1;

static u32 VertexArrays[VERTEX_ARRAYS];
static u32 VertexBuffers[VERTEX_BUFFERS];
static u32 ShaderPrograms[SHADER_PROGRAMS];

static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);
static void FramebufferResizeCallback( GLFWwindow *window, const i32 width, const i32 height);

void kRender::LoadScene( kScene_t *scene) {
    glBindVertexArray( VertexArrays[ scene->ID ] );
}

void kRender::RenderCurrentScene() const {
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
}


void kRender::SetWindow( GLFWwindow * new_window ) {
    this->window = new_window;
}

void kRender::Draw() const {

    glClear(GL_COLOR_BUFFER_BIT);

    RenderCurrentScene();

    glfwSwapBuffers((GLFWwindow*)window);
    glfwPollEvents();   //TODO(Kasper): Where is this supposed to be?
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
