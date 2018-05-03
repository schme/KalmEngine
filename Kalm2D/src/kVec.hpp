/**
 *
 * kVec.hpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018 
 */

#ifndef KVEC_HPP_
#define KVEC_HPP_


#include "Types.h"

class vec2 {
    public:
    r32 x; r32 y;
};

class vec3 {
    public:
    r32 x; r32 y; r32 z;
};

class vec4 {
    public:
    r32 x; r32 y; r32 z; r32 w;
};


#ifdef KVEC_IMPLEMENTATION

#endif
#endif /* end of include guard: KVEC_HPP_ */
