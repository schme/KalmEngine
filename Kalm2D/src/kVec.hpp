/**
 *
 * kVec.hpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

/**
 * TODO(Kasper): Move intrinsics to their own file.
 */

#ifndef KVEC_HPP_
#define KVEC_HPP_

#include <xmmintrin.h>

#include "Types.h"


class vec2 {
    public:
    union {
        struct {
            r32 x; r32 y;
        };
        struct {
            r32 r; r32 g;
        };
        struct {
            r32 v[2];
        };
    };
    vec2( r32 x, r32 y) : x(x), y(y) { }
    vec2( r32 value) : x(value), y(value) { }
};


class vec3 {
    public:
    union {
        struct {
            r32 x; r32 y; r32 z; r32 w;
        };
        struct {
            r32 r; r32 g; r32 b; r32 a;
        };
        struct {
            r32 quad[4];
        };
        struct {
            __m128 sQuad;
        };
    };

    vec3( r32 x, r32 y, r32 z) :
        x(x), y(y), z(z), w(0.0f) { }

    vec3( r32 value ) :
        x(value), y(value), z(value), w(0.0f) { }

};


class vec4 {
    public:
    union {
        struct {
            r32 x; r32 y; r32 z; r32 w;
        };
        struct {
            r32 r; r32 g; r32 b; r32 a;
        };
        struct {
            r32 quad[4];
        };
        struct {
            __m128 sQuad;
        };
    };
};


inline vec3
operator*(vec3 a, r32 b) {
    vec3 result = vec3(a.x * b, a.y * b, a.z * b);
    return result;
}

inline r32
Sqrt( r32 val ) {
    r32 result = _mm_cvtss_f32( _mm_sqrt_ss( _mm_set_ss( val )));
    return result;
}

inline r32
Dot( vec3 a, vec3 b) {
    r32 result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}

inline r32
LengthSq( vec3 a ) {
    r32 result = Dot( a, a );
    return result;
}

inline r32
Length( vec3 a ) {
    r32 result = Sqrt( LengthSq( a ));
    return result;
}

inline vec3
Normalized( vec3 a ) {
    vec3 result = a * 1.0f;
    return result;
}


#ifdef KVEC_IMPLEMENTATION


#endif
#endif /* end of include guard: KVEC_HPP_ */
