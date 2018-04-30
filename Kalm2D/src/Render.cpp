/**
 *
 * Render.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Types.h"
#include "Render.h"

static u32 testVAO = 0;
static u32 testVBO = 0;
static u32 testEBO = 0;
static u32 testShaderProgram = 0;


const char *vertexPassShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"};\n\0";


const char *fragmentPassShader = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.0f, 0.8f, 0.8f, 1.0f);\n"
"}\n\0";


static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);
static void FramebufferResizeCallback( GLFWwindow *window, const i32 width, const i32 height);

void kRender::Initialize() {

    glfwSetFramebufferSizeCallback( kRender::window, FramebufferResizeCallback);
    glfwSetWindowSizeCallback( kRender::window, ResizeCallback);

    i32 width, height;
    glfwGetFramebufferSize( kRender::window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor( 0.1f, 0.1f, 0.1f, 1.0f);


    /**
     * TRIANGLE TEST INIT
     */

    float vertices[] = {
        0.9f, 0.9f, 0.0f,
        0.9f, -0.9f, 0.0f,
        -0.9f, -0.9f, 0.0f,
        -0.9f, 0.9f, 0.0f
    };

    u32 indices[] = {
        0,1,3,
        1,2,3
    };


    b32 success = false;

    glGenVertexArrays( 1, &testVAO);
    glGenBuffers( 1, &testVBO);
    glGenBuffers( 1, &testEBO);

    glBindVertexArray( testVAO);

    glBindBuffer( GL_ARRAY_BUFFER, testVBO);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, testEBO);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    u32 vertexShader;
    vertexShader = glCreateShader( GL_VERTEX_SHADER);
    glShaderSource( vertexShader, 1, &vertexPassShader, NULL);
    glCompileShader( vertexShader);

    success = false;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success);
    if( !success ) {
        this->PrintOpenGLShaderError( vertexShader, "Failed to compile vertex shader");
    }

    u32 fragmentShader;
    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER);
    glShaderSource( fragmentShader, 1, &fragmentPassShader, NULL);
    glCompileShader( fragmentShader);

    success = false;
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success);
    if( !success ) {
        this->PrintOpenGLShaderError( fragmentShader, "Failed to compile vertex shader");
    }

    testShaderProgram = glCreateProgram();

    glAttachShader( testShaderProgram, vertexShader);
    glAttachShader( testShaderProgram, fragmentShader);
    glLinkProgram( testShaderProgram);

    success = false;
    glGetProgramiv( testShaderProgram, GL_LINK_STATUS, &success);
    if( !success ) {
        this->PrintOpenGLProgramError( testShaderProgram, "Failed to link shaders.");
    }

    glUseProgram( testShaderProgram);
    glDeleteShader( vertexShader);
    glDeleteShader( fragmentShader);

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0);
}


void kRender::SetWindow( GLFWwindow * new_window ) {
    this->window = new_window;
}


void kRender::DrawTestImage( kImage_t *image) const {
}

void kRender::Draw() const {

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram( testShaderProgram);
    glBindVertexArray( testVAO);

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers((GLFWwindow*)window);
    glfwPollEvents();   //TODO(Kasper): Where is this supposed to be?
}


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

void kRender::PrintOpenGLShaderError( u32 shader, const char *message) const {
    char infoLog[512];
    glGetShaderInfoLog( shader, 512, NULL, infoLog);
    PRINTL_STR(message);
    PRINTL_STR( infoLog);
}
