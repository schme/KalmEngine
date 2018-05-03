/**
 *
 * kVector.h
 *
 * Vectors and matrice definitions.
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#ifndef KVECTOR_H_
#define KVECTOR_H_

#include "Types.h"

union vec2 {
    struct {
        f32 x, y;
    };
    struct {
        f32 u, v;
    };
    f32 E[2];
};

union vec3 {
    struct {
        f32 x, y, z;
    };
    struct {
        f32 r, g, b;
    };
    struct {
        f32 u, v, ignored0_;
    };
    struct {
        vec2 xy;
        f32 ignored1_;
    };
    struct {
        vec2 uv;
        f32 ignored2_;
    };
    f32 E[3];
};

union vec4 {
    struct {
        union {
            vec3 xyz;
            struct {
                f32 x, y, z;
            };
        };
        f32 w;
    };
    struct {
        union {
            vec3 rgb;
            struct {
                f32 r, g, b;
            };
        };
        f32 a;
    };
    struct {
        vec2 xy;
        f32 ignored0_;
        f32 ignored1_;
    };
    struct {
        f32 ignored2_;
        vec2 yz;
        f32 ignored3_;
    };
    struct {
        f32 ignored4_;
        f32 ignored5_;
        vec2 zw;
    };
    struct {
        f32 E[4];
    };
};

struct m4x4 {
    f32 E[4][4];
};


/**
 * Not really constructors
 */
inline vec3 Vec3( f32 x, f32 y, f32 z ) {
    vec3 result;

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

inline vec3 Vec3( f32 v ) {
    vec3 result;

    result.x = v;
    result.y = v;
    result.z = v;

    return result;
}

/**
 * Operators
 */
inline vec3 operator*( vec3 a, f32 b) {
    vec3 result = Vec3( a.x * b, a.y * b, a.z * b);
    return result;
}

inline vec3 & operator*=( vec3 &a, f32 b ) {
    a = a * b;
    return a;
}

inline vec3 operator-( vec3 a ) {
    vec3 result = Vec3( -a.x, -a.y, -a.z );
    return result;
}


inline vec3 operator+( vec3 a, vec3 b) {
    vec3 result = Vec3( a.x + b.x, a.y + b.y, a.z + b.z);
    return result;
}

inline vec3 & operator+=( vec3& a, vec3 b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

inline vec3 operator-( vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

inline vec3& operator-=( vec3& a, vec3 b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

inline vec3 operator/( vec3 a, f32 b) {
    vec3 result;
    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    return result;
}

inline vec3& operator/=( vec3 &a, f32 b) {
    a.x = a.x / b;
    a.y = a.y / b;
    a.z = a.z / b;
    return a;
}

#endif /* end of include guard: KVECTOR_H_ */
