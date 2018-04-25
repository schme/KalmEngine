#ifndef WIN_MAIN_H_
#define WIN_MAIN_H_

#include <windows.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#include <intrin.h>
#include <stdio.h>

#include "kalm_shared.h"
#include "k_types.h"

const u8 GL_Version_Major = 3;
const u8 GL_Version_Minor = 1;

struct Win_WindowDimensions_t {
    i32 width;
    i32 height;
};

#endif /* end of include guard: WIN_MAIN_H_ */
