#include "kalm2d.h"

static KalmInput_t currentInputState = {};

void KalmUpdate( const KalmInput_t &input) {
    HandleInput( input );
}


void KalmResize( const i32 width, const i32 height ) {
    r32 windowAspectRatio = (r32)width / (r32)height;

    //glViewport((GLint)0, (GLint)0, (GLsizei)width, (GLsizei)height);
}


void HandleInput( const KalmInput_t &input) {
    currentInputState = input;
}
