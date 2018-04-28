#ifndef KALM2D_H_
#define KALM2D_H_

#include "kalm_shared.h"
#include "win_Kalm2D.h"

#include <glad/glad.h>
#include "glfw/glfw3.h"

/* The title bar text */
const char *title = "Kalm2D";

const u8 GL_Version_Major = 3;
const u8 GL_Version_Minor = 1;

class Kalm2D : public kGame {
    public:
        static gameImport_t * system;
        static gameExport_t gameExport;

        static GLFWwindow * window;

        b32 Initialize();
        i32 Loop ();
        void Terminate();
    private:
};

#endif /* end of include guard: KALM2D_H_ */
