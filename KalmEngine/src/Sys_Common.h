/**
 *
 * kCommonSystem
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */
#ifndef COMMONSYSTEM_H_
#define COMMONSYSTEM_H_

#include "../include/glfw/glfw3.h"

#include "Systems.h"
#include "Types.h"
#include "KalmShared.h"

class kCommonSystem : public CommonSystem {
    static gameInput_t inputState[2];
    static gameInput_t *oldState;
    static gameInput_t *newState;

    public:

        gameInput_t *   GetOldState();
        gameInput_t *   GetNewState();

        void            Initialize();
        void            SetWindow( GLFWwindow *new_window);
        gameInput_t *   GetInput() const;
        b32             IfWindowShouldClose() const;
        f64             GetTime() const;
        void            PollEvents() const;
    private:
        GLFWwindow *    window;

        void            ToggleButton( gameButtonState_t *key, const i32 action);
};

#endif /* end of include guard: COMMONSYSTEM_H_ */
