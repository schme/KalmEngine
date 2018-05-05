/**
 *
 * Render.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#ifndef RENDER_H_
#define RENDER_H_

#include "Systems.h"
#include "glfw/glfw3.h"
#include "Scene.h"

class kRender : public RenderSystem {
    public:

        /** RenderSystem overrides */
        void Draw() const;

        /** SystemLocal methods */
        void Initialize();
        void SetWindow( GLFWwindow * window);
        void LoadScene( kScene_t *scene);
        void SetGroupModelView( mat4 modelView);
        void SetPerspective( mat4 perspective);

    private:
        GLFWwindow *    window;
        void RenderCurrentScene() const;
        void PrintOpenGLProgramError( u32 program, const char *message = "") const;
        void PrintOpenGLShaderError( u32 shader, const char *message = "") const;
};

#endif /* end of include guard: RENDER_H_ */
