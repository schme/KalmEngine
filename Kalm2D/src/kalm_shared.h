#ifndef KALM_SHARED_H_
#define KALM_SHARED_H_

#include <string>
#include <cstdlib>

#include "stdafx.h"
#include "glfw/glfw3.h"
#include "glfw/glfw3native.h"
#include "linmath.h"
#include "Types.h"

#define PRINTSTR

b32 InitializeGraphicsContext();
b32 KalmLoop();
void KalmTerminate();

#endif /* end of include guard: KALM_SHARED_H_ */
