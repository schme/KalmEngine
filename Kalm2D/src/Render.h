/**
 *
 * Render.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Systems.h"
#include "glfw/glfw3.h"

#ifndef RENDER_H_
#define RENDER_H_

class kRender : public RenderSystem {
    public:
        void Initialize();
        void Draw() const;
        void SetWindow( GLFWwindow * window);
    private:
        GLFWwindow *    window;
};

#endif /* end of include guard: RENDER_H_ */
