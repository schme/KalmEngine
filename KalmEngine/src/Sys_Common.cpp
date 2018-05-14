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
static void MouseScrollCallback(GLFWwindow* window, const f64 xoffset, const f64 yoffset);
static void WindowFocusCallback( GLFWwindow* wnd, const i32 focused);


void kCommonSystem::Initialize() {
    glfwSetKeyCallback( this->window, KeyCallback);
    glfwSetCursorPosCallback( this->window, CursorPositionCallback);
    glfwSetMouseButtonCallback( this->window, MouseButtonCallback);
    glfwSetScrollCallback( this->window, MouseScrollCallback);

    glfwSetInputMode( this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void kCommonSystem::SetWindow( GLFWwindow *new_window) {
    this->window = new_window;
}

gameInput_t *kCommonSystem::GetInputState() {
    gameInput_t *r = this->inputState;
    return r;
}

gameInput_t *kCommonSystem::GetOldState() {
    gameInput_t *r = this->oldState;
    return r;
}

gameInput_t *kCommonSystem::GetNewState() {
    gameInput_t *r = this->newState;
    return r;
}

/**
 * Clear old state and swap pointers
 */
void kCommonSystem::SwapAndClearState() {
    gameInput_t *temp = this->newState;
    this->newState = this->oldState;
    *this->newState = {};
    this->oldState = temp;

    for( u32 i=0; i < this->newState->inputArrayLength; i++) {
        this->newState->buttons[i].endedDown = this->oldState->buttons[i].endedDown;
    }
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
    if( action == GLFW_REPEAT ) return;

    (newButton->toggleCount)++;
    if( oldButton->endedDown && action != GLFW_RELEASE ) {
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

    (void)wnd;

    static b32 firstRun = true;

    static f32 lastPosX = 0;
    static f32 lastPosY = 0;

    mouseInput_t * newMouse = &g_Common->GetNewState()->mouseInput;

    newMouse->posX = (f32)posx;
    newMouse->posY = (f32)posy;

    if( !firstRun) {

        newMouse->offsetX = newMouse->posX - lastPosX;
        newMouse->offsetY = lastPosY - newMouse->posY;
    }

    lastPosX = newMouse->posX;
    lastPosY = newMouse->posY;

    firstRun = false;
}

void MouseButtonCallback( GLFWwindow* wnd, const i32 button, const i32 action, const i32 mods) {
    (void)wnd;
    (void)mods;

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

void MouseScrollCallback( GLFWwindow* wnd, const f64 xoffset, const f64 yoffset) {

    (void)xoffset;
    (void)wnd;

    g_Common->GetNewState()->mouseInput.scrollOffsetY = (f32)yoffset;
}

void WindowFocusCallback( GLFWwindow* wnd, const i32 focused) {
    if( !focused) {
        glfwSetCursorPosCallback( wnd, nullptr);
    } else {
        glfwSetCursorPosCallback( wnd, CursorPositionCallback);
    }
}

/**
 * TODO(Kasper): Map actions to keys somewhere else
 */
void KeyCallback( GLFWwindow* wnd, const i32 key, const i32 scancode, const i32 action, const i32 mods) {
    (void)scancode;
    (void)mods;
    /*
     * TODO(Kasper): Handle this properly in the gamecode
     */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(wnd, GLFW_TRUE);
    }

    gameInput_t *oldState = g_Common->GetOldState();
    gameInput_t *newState = g_Common->GetNewState();

    switch( key )
    {
        case ( GLFW_KEY_W ): {
            gameButtonState_t *oldButton = &oldState->up;
            gameButtonState_t *newButton = &newState->up;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_A ): {
            gameButtonState_t *oldButton = &oldState->left;
            gameButtonState_t *newButton = &newState->left;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_S ): {
            gameButtonState_t *oldButton = &oldState->down;
            gameButtonState_t *newButton = &newState->down;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_D ): {
            gameButtonState_t *oldButton = &oldState->right;
            gameButtonState_t *newButton = &newState->right;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_SPACE ): {
            gameButtonState_t *oldButton = &oldState->actionSpace;
            gameButtonState_t *newButton = &newState->actionSpace;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_C ): {
            gameButtonState_t *oldButton = &oldState->actionC;
            gameButtonState_t *newButton = &newState->actionC;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_ENTER ): {
            gameButtonState_t *oldButton = &oldState->actionEnter;
            gameButtonState_t *newButton = &newState->actionEnter;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_ESCAPE ): {
            gameButtonState_t *oldButton = &oldState->actionEsc;
            gameButtonState_t *newButton = &newState->actionEsc;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_Q ): {
            gameButtonState_t *oldButton = &oldState->actionQ;
            gameButtonState_t *newButton = &newState->actionQ;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_E ): {
            gameButtonState_t *oldButton = &oldState->actionE;
            gameButtonState_t *newButton = &newState->actionE;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_R ): {
            gameButtonState_t *oldButton = &oldState->actionR;
            gameButtonState_t *newButton = &newState->actionR;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F ): {
            gameButtonState_t *oldButton = &oldState->actionF;
            gameButtonState_t *newButton = &newState->actionF;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_LEFT_SHIFT ): {
            gameButtonState_t *oldButton = &oldState->l_shift;
            gameButtonState_t *newButton = &newState->l_shift;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_LEFT_CONTROL ): {
            gameButtonState_t *oldButton = &oldState->l_ctrl;
            gameButtonState_t *newButton = &newState->l_ctrl;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F1 ): {
            gameButtonState_t *oldButton = &oldState->actionF1;
            gameButtonState_t *newButton = &newState->actionF1;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F2 ): {
            gameButtonState_t *oldButton = &oldState->actionF2;
            gameButtonState_t *newButton = &newState->actionF2;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F3 ): {
            gameButtonState_t *oldButton = &oldState->actionF3;
            gameButtonState_t *newButton = &newState->actionF3;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F4 ): {
            gameButtonState_t *oldButton = &oldState->actionF4;
            gameButtonState_t *newButton = &newState->actionF4;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F5 ): {
            gameButtonState_t *oldButton = &oldState->actionF5;
            gameButtonState_t *newButton = &newState->actionF5;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F6 ): {
            gameButtonState_t *oldButton = &oldState->actionF6;
            gameButtonState_t *newButton = &newState->actionF6;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F7 ): {
            gameButtonState_t *oldButton = &oldState->actionF7;
            gameButtonState_t *newButton = &newState->actionF7;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F8 ): {
            gameButtonState_t *oldButton = &oldState->actionF8;
            gameButtonState_t *newButton = &newState->actionF8;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F9 ): {
            gameButtonState_t *oldButton = &oldState->actionF9;
            gameButtonState_t *newButton = &newState->actionF9;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F10 ): {
            gameButtonState_t *oldButton = &oldState->actionF10;
            gameButtonState_t *newButton = &newState->actionF10;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F11 ): {
            gameButtonState_t *oldButton = &oldState->actionF11;
            gameButtonState_t *newButton = &newState->actionF11;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        case ( GLFW_KEY_F12 ): {
            gameButtonState_t *oldButton = &oldState->actionF12;
            gameButtonState_t *newButton = &newState->actionF12;
            ToggleButton( oldButton, newButton, action );
            break;
        }
        default: {
            /** unhandled buttons */
            break;
        }
    }

}

