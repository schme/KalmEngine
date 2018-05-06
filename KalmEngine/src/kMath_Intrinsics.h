/**
 *
 * kMath_intrinsics.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#ifndef KMATH_INTRINSICS_H_
#define KMATH_INTRINSICS_H_

#include <intrin.h>
#include "Types.h"

inline f32 Sqrt( f32 val ) {
    f32 result = _mm_cvtss_f32( _mm_sqrt_ss( _mm_set_ss( val )));
    return result;
}

#endif /* end of include guard: KMATH_INTRINSICS_H_ */
