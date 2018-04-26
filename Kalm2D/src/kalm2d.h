#ifndef KALM2D_H_
#define KALM2D_H_

#include <cstdio>
#include <glad/glad.h>
#include "kalm_shared.h"

/* The title bar text */
const char *title = "Kalm2D";

const u8 GL_Version_Major = 3;
const u8 GL_Version_Minor = 1;

static void KeyCallback( GLFWwindow* window, const i32 key, const i32 scancode, const i32 action, const i32 mods);
static void ErrorCallback( const i32 error, const char* description);
static void ResizeCallback( GLFWwindow* window, const i32 numer, const i32 denom);

#endif /* end of include guard: KALM2D_H_ */
