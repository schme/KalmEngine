#ifndef KALM_SHARED_H_
#define KALM_SHARED_H_

#include "glfw3.h"
#include "k_types.h"

/* holds toggle states */
struct KalmInput_t {
    r64 deltaTime;
    u64 frame;

    b32 KEY_W;
    b32 KEY_A;
    b32 KEY_S;
    b32 KEY_D;
    b32 KEY_Q;
    b32 KEY_E;

    b32 KEY_UP;
    b32 KEY_LEFT;
    b32 KEY_DOWN;
    b32 KEY_RIGHT;

    b32 KEY_SPACE;
    b32 KEY_ESCAPE;
};

void KalmUpdate( const KalmInput_t &input);
void KalmResize( const i32 width, const i32 height);

#endif /* end of include guard: KALM_SHARED_H_ */
