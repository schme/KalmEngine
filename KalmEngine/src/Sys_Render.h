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
#include "../include/glfw/glfw3.h"
#include "Scene.h"

class kRender : public RenderSystem {
    public:

        /** RenderSystem overrides */
        void Draw() const;

        /** SystemLocal methods */
        void Initialize();
        void SetWindow( GLFWwindow * window);
        void LoadTexture( kTexture_t* image);
        void LoadScene( kScene_t *scene);
        void SetGroupModelView( mat4 modelView);
        void SetPerspectiveMatrix( mat4 perspective);
        void LoadVertices( kMesh_t *verts, const u32 buffer_id ) const;

    private:
        GLFWwindow *    window;
        void PrintOpenGLProgramError( u32 program, const char *message = "") const;
        void PrintOpenGLShaderError( u32 shader, const char *message = "") const;
};

#endif /* end of include guard: RENDER_H_ */
