/**
 *
 * kCommonSystem.cpp
 *
 * Consists of Input, Timers, Messages and other miscellenious
 * functions
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Sys_Common.h"
#include "Sys_Shared.h"

static void KeyCallback( GLFWwindow* window, const i32 key, const i32 scancode, const i32 action, const i32 mods);
static void CursorPositionCallback( GLFWwindow* wnd, const f64 posx, const f64 posy);
static void MouseButtonCallback( GLFWwindow* wnd, const i32 button, const i32 action, const i32 mods);

gameInput_t kCommonSystem::inputState[2] = {};
gameInput_t *kCommonSystem::oldState = &kCommonSystem::inputState[0];
gameInput_t *kCommonSystem::newState = &kCommonSystem::inputState[1];

void kCommonSystem::Initialize() {
    glfwSetKeyCallback( this->window, KeyCallback);
    glfwSetCursorPosCallback( this->window, CursorPositionCallback);
    glfwSetMouseButtonCallback( this->window, MouseButtonCallback);
}

void kCommonSystem::SetWindow( GLFWwindow *new_window) {
    this->window = new_window;
}


gameInput_t *kCommonSystem::GetOldState() {
    return this->oldState;
}

gameInput_t *kCommonSystem::GetNewState() {
    return this->newState;
}

f64 kCommonSystem::GetTime() const {
    return glfwGetTime();
}

b32 kCommonSystem::IfWindowShouldClose() const {
    return glfwWindowShouldClose( this->window);
}

void kCommonSystem::PollEvents() const {
    glfwPollEvents();
}

void ToggleButton( gameButtonState_t *button, const i32 action ) {
    ++( button->toggleCount );
    if( action == GLFW_PRESS) {
        button->endedDown = true;
    } else {
        button->endedDown = false;
    }
}

/**
 * TODO(Kasper): check if we need double
 */
void CursorPositionCallback( GLFWwindow* wnd, const f64 posx, const f64 posy ) {
    g_Common->GetNewState()->mouseInput.posx = (f32)posx;
    g_Common->GetNewState()->mouseInput.posx = (f32)posy;
}

void MouseButtonCallback( GLFWwindow* wnd, const i32 button, const i32 action, const i32 mods) {
    switch( button )
    {
        case ( GLFW_MOUSE_BUTTON_RIGHT ): {
            gameButtonState_t *gButton = &g_Common->GetNewState()->mouseInput.right;
            ToggleButton( gButton, action);
            break;
        }
        case ( GLFW_MOUSE_BUTTON_LEFT ): {
            gameButtonState_t *gButton = &g_Common->GetNewState()->mouseInput.left;
            ToggleButton( gButton, action);
            break;
        }
        default: {
            /** unhandled mousebutton */
        }

    }
}

/**
 * TODO(Kasper): Map actions to keys somewhere else
 */
void KeyCallback( GLFWwindow* wnd, const i32 key, const i32 scancode, const i32 action, const i32 mods) {

    /*
     * TODO(Kasper): Handle this properly in the gamecode
     */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(wnd, GLFW_TRUE);
    }

    switch( key )
    {
        case ( GLFW_KEY_W ): {
            gameButtonState_t *button = &g_Common->GetNewState()->up;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_A ): {
            gameButtonState_t *button = &g_Common->GetNewState()->left;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_S ): {
            gameButtonState_t *button = &g_Common->GetNewState()->down;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_D ): {
            gameButtonState_t *button = &g_Common->GetNewState()->right;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_SPACE ): {
            gameButtonState_t *button = &g_Common->GetNewState()->actionSpace;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_ENTER ): {
            gameButtonState_t *button = &g_Common->GetNewState()->actionEnter;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_ESCAPE ): {
            gameButtonState_t *button = &g_Common->GetNewState()->actionEsc;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_Q ): {
            gameButtonState_t *button = &g_Common->GetNewState()->actionQ;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_E ): {
            gameButtonState_t *button = &g_Common->GetNewState()->actionE;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_R ): {
            gameButtonState_t *button = &g_Common->GetNewState()->actionR;
            ToggleButton( button, action );
            break;
        }
        case ( GLFW_KEY_F ): {
            gameButtonState_t *button = &g_Common->GetNewState()->actionF;
            ToggleButton( button, action );
            break;
        }
        default: {
            /** unhandled buttons */
            break;
        }
    }

}

