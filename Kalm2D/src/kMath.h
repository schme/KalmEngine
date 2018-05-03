/**
 *
 * kMath.hpp - One-file math library
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#ifndef KMATH_H_
#define KMATH_H_

#include "kMath_intrinsics.h"
#include "kVector.h"

f32 Sqrt( f32 val );
f32 Dot( vec3 a, vec3 b );
f32 LenthSq( vec3 a );
f32 Length( vec3 a );
vec3 Normalized( vec3 a );


inline f32
Dot( vec3 a, vec3 b) {
    f32 result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}

inline f32
LengthSq( vec3 a ) {
    f32 result = Dot( a, a );
    return result;
}

inline f32
Length( vec3 a ) {
    f32 result = Sqrt( LengthSq( a ));
    return result;
}

inline vec3
Normalized( vec3 a ) {
    vec3 result = a * 1.0f;
    return result;
}


#endif /* end of include guard: KMATH_HPP_ */
