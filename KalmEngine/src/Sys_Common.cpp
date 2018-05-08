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

gameInput_t *kCommonSystem::GetInput() {
    return this->inputState;
}

gameInput_t *kCommonSystem::GetOldState() {
    return this->oldState;
}

gameInput_t *kCommonSystem::GetNewState() {
    return this->newState;
}

/**
 * Clear old state and swap pointers
 */
void kCommonSystem::SwapAndClearState() {
    gameInput_t *temp = this->newState;
    this->oldState = {};
    this->newState = this->oldState;
    this->oldState = temp;
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

void ToggleButton( gameButtonState_t *oldButton, gameButtonState_t *newButton, const i32 action ) {
    ++( newButton->toggleCount );
    if( action != GLFW_PRESS && oldButton->endedDown ) {
        newButton->endedDown = true;
    } else if ( action == GLFW_PRESS ) {
        newButton->endedDown = true;
    } else {
        newButton->endedDown = false;
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
            gameButtonState_t *oldButton = &g_Common->GetOldState()->mouseInput.right;
            gameButtonState_t *newButton = &g_Common->GetNewState()->mouseInput.right;
            ToggleButton( oldButton, newButton, action);
            break;
        }
        case ( GLFW_MOUSE_BUTTON_LEFT ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->mouseInput.left;
            gameButtonState_t *newButton = &g_Common->GetNewState()->mouseInput.left;
            ToggleButton( oldButton, newButton, action);
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
            gameButtonState_t *oldButton = &g_Common->GetOldState()->up;
            gameButtonState_t *newButton = &g_Common->GetNewState()->up;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_A ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->left;
            gameButtonState_t *newButton = &g_Common->GetNewState()->left;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_S ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->down;
            gameButtonState_t *newButton = &g_Common->GetNewState()->down;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_D ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->right;
            gameButtonState_t *newButton = &g_Common->GetNewState()->right;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_SPACE ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->actionSpace;
            gameButtonState_t *newButton = &g_Common->GetNewState()->actionSpace;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_ENTER ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->actionEnter;
            gameButtonState_t *newButton = &g_Common->GetNewState()->actionEnter;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_ESCAPE ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->actionEsc;
            gameButtonState_t *newButton = &g_Common->GetNewState()->actionEsc;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_Q ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->actionQ;
            gameButtonState_t *newButton = &g_Common->GetNewState()->actionQ;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_E ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->actionE;
            gameButtonState_t *newButton = &g_Common->GetNewState()->actionE;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_R ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->actionR;
            gameButtonState_t *newButton = &g_Common->GetNewState()->actionR;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F ): {
            gameButtonState_t *oldButton = &g_Common->GetOldState()->actionF;
            gameButtonState_t *newButton = &g_Common->GetNewState()->actionF;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        default: {
            /** unhandled buttons */
            break;
        }
    }

}

