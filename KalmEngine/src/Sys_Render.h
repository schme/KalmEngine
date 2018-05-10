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
#include "KalmShared.h"

#define MAX_RENDER_GROUPS 5

class kRender : public RenderSystem {
    public:

        /** RenderSystem overrides */
        void Draw() const;
        void LoadTestScene( kScene_t *scene ) const;
        void DrawTestScene( kScene_t *scene) const;
        void DrawObject_r(const kObject *obj, const mat4 parentModelView, const vec3 rotation, const mat4 view, const renderType_t *rndGroup ) const;
        void SetProjectionMatrix( const u32 shaderID, const mat4 projection) const;
        void SetModelViewMatrix( const u32 shaderId, const mat4 modelView) const;
        void SetMatrixUniform( const u32 shaderID, const char *name, const mat4 matrix) const;

        /** SystemLocal methods */
        void Initialize();
        void SetWindow( GLFWwindow * window);
        void LoadTexture( kTexture_t* image);
        void LoadScene( kScene_t *scene);
        void LoadVertices( const kMesh_t *verts, const renderType_t *type ) const;
        void CheckToggleWireframe() const;

    private:
        GLFWwindow *    window;
        renderType_t renderGroups[MAX_RENDER_GROUPS];
        void PrintOpenGLProgramError( u32 program, const char *message = "") const;
        void PrintOpenGLShaderError( u32 shader, const char *message = "") const;
};

#endif /* end of include guard: RENDER_H_ */
