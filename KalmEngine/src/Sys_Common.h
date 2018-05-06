/**
 *
 * kCommonSystem
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */
#ifndef COMMONSYSTEM_H_
#define COMMONSYSTEM_H_

#include "Systems.h"
#include "Types.h"
#include "glfw/glfw3.h"

class kCommonSystem : public CommonSystem {
    public:
        void    Initialize();
        void    SetWindow( GLFWwindow *new_window);
        b32     IfWindowShouldClose() const;
        f64     GetTime() const;
    private:
        GLFWwindow *    window;
};


static void KeyCallback( GLFWwindow* window, const i32 key, const i32 scancode, const i32 action, const i32 mods);


#endif /* end of include guard: COMMONSYSTEM_H_ */
