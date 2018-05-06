/**
 *
 * kCommonSystem.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Sys_Common.h"

void kCommonSystem::Initialize() {
    glfwSetKeyCallback( this->window, KeyCallback);
}

void kCommonSystem::SetWindow( GLFWwindow *new_window) {
    this->window = new_window;
}

f64 kCommonSystem::GetTime() const {
    return glfwGetTime();
}

b32 kCommonSystem::IfWindowShouldClose() const {
    //TODO(Kasper): Implement this here!
    return glfwWindowShouldClose( this->window);
}

void KeyCallback(GLFWwindow* wnd, const i32 key, const i32 scancode, const i32 action, const i32 mods) {
    /* Close window */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(wnd, GLFW_TRUE);
    }
}

