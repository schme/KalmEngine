#ifndef WIN_MAIN_H_
#define WIN_MAIN_H_

#include <windows.h>
#include <cstdio>

#include <intrin.h>

#include <glad/glad.h>
#include "kalm_shared.h"
#include "k_types.h"

const u8 GL_Version_Major = 3;
const u8 GL_Version_Minor = 1;

static void KeyCallback( GLFWwindow* window, const i32 key, const i32 scancode, const i32 action, const i32 mods);
void ErrorCallback( const i32 error, const char* description);
void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);


#endif /* end of include guard: WIN_MAIN_H_ */
