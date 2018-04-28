/**
 *
 * Render.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Types.h"
#include "Render.h"

static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);

void kRender::Initialize() {

    i32 width, height;
    glfwGetFramebufferSize( kRender::window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback( kRender::window, ResizeCallback);

}


void kRender::SetWindow( GLFWwindow * new_window ) {
    this->window = new_window;
}


void kRender::Draw() const {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers((GLFWwindow*)window);
    glfwPollEvents();
    return;
}

void ResizeCallback( GLFWwindow* wnd, const i32 numer, const i32 denom) {
    i32 width, height;
    glfwGetFramebufferSize( wnd, &width, &height);
    glfwSetWindowSize( wnd, width*numer, height*denom);
}

