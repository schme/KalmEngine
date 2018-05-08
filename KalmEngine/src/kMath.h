/**
 *
 * kMath.hpp - One-file math library
 *
 * TODO(Kasper): Implement trigonometric functions as intrinsics
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#define PI 3.14159265359f

#ifndef KMATH_H_
#define KMATH_H_

#include <math.h>

#include "kMath_Intrinsics.h"
#include "kVector.h"

inline f32 Dot( vec3 a, vec3 b) {
    f32 result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}

inline f32 LengthSq( vec3 a ) {
    f32 result = Dot( a, a );
    return result;
}

inline f32 Length( vec3 a ) {
    f32 result = Sqrt( LengthSq( a ));
    return result;
}

inline vec3 Normalized( vec3 a ) {
    vec3 result = a * 1.0f;
    return result;
}

inline vec3 Cross( vec3 a, vec3 b ) {
    vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

inline f32 Radians( f32 degrees ) {
    return degrees * PI / 180.0f;
}

inline mat4 Scale( mat4 A, vec3 scale) {
    mat4 M = A;

    M.A[0][0] *= scale.x;
    M.A[1][1] *= scale.y;
    M.A[2][2] *= scale.z;

    return M;
}

/** TODO(Kasper): Optimise */
inline vec4 Transform( mat4 A, vec4 p) {
    vec4 r;

    r.x = p.x*A.A[0][0] + p.y*A.A[0][1] + p.z*A.A[0][2] + p.w*A.A[0][3];
    r.y = p.x*A.A[1][0] + p.y*A.A[1][1] + p.z*A.A[1][2] + p.w*A.A[1][3];
    r.z = p.x*A.A[2][0] + p.y*A.A[2][1] + p.z*A.A[2][2] + p.w*A.A[2][3];
    r.w = p.x*A.A[3][0] + p.y*A.A[3][1] + p.z*A.A[3][2] + p.w*A.A[3][3];

    return r;
}

inline mat4 GetIdentityMat() {
    mat4 M = {{{
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    }}};
    return M;
}

static mat4
Translate( mat4 A, vec3 t ) {
    mat4 M = A;
    M.A[0][3] += t.x;
    M.A[1][3] += t.y;
    M.A[2][3] += t.z;
    return M;
}

static mat4
Translate( vec3 t ) {
    mat4 M = GetIdentityMat();
    M.A[0][3] += t.x;
    M.A[1][3] += t.y;
    M.A[2][3] += t.z;
    return M;
}

inline mat4 RotationX( f32 angle) {
    f32 c = cosf( angle );
    f32 s = sinf( angle );

    mat4 M = {
    {{{ 1, 0,   0,  0},
      { 0, c,  -s,  0},
      { 0, s,   c,  0},
      { 0, 0,   0,  1}}}
    };
    return M;
}

inline mat4 RotationY( f32 angle) {
    f32 c = cosf( angle );
    f32 s = sinf( angle );

    mat4 M = {
    {{{ c, 0,   s,  0},
      { 0, 1,   0,  0},
      {-s, 0,   c,  0},
      { 0, 0,   0,  1}}}
    };
    return M;
}

inline mat4 RotationZ( f32 angle) {
    f32 c = cosf( angle );
    f32 s = sinf( angle );

    mat4 M = {
    {{{ c,-s,   0,  0},
      { s, c,   0,  0},
      { 0, 0,   1,  0},
      { 0, 0,   0,  1}}}
    };
    return M;
}

inline mat4 Transpose( mat4 A ) {
    mat4 M;
    for( int j = 0; j < 4; ++j ) {
        for( int i = 0; i < 4; ++i ) {
            M.A[j][i] = A.A[i][j];
        }
    }
    return M;
}

inline mat4
GetPerspectiveMat( f32 FOV, f32 aspect, f32 nearPlane, f32 farPlane ) {
    f32 n = nearPlane;
    f32 f = farPlane;
    f32 scale = tanf( FOV * 0.5f * PI / 180.0f) * n;
    f32 r = aspect * scale;
    f32 l = -r;
    f32 t = scale;
    f32 b = -t;

    mat4 M = {{{
        { (2*n)/(r-l),           0,              0,  0 },
        {           0, (2*n)/(t-b),              0,  0 },
        { (r+l)/(r-l), (t+b)/(t-b),   -(f+n)/(f-n), -1 },
        {           0,           0, (-2*f*n)/(f-n),  0 }
    }}};

    return M;
}

/**
 * eg. ( width/height, 0.1f, 100.0f)
 * Returns inverse mat
 */
inline mat4_inv
GetInvOrthoMat( f32 aspect, f32 nearPlane, f32 farPlane )
{
    f32 f = farPlane;
    f32 n = nearPlane;

    f32 a = 1.0f;
    f32 b = aspect;

    f32 d = 2.0f/(n-f);
    f32 e = (n+f)/(n-f);

    mat4_inv M = {
        /** Forward */
     {{{{ a, 0, 0, 0},
        { 0, b, 0, 0},
        { 0, 0, d, e},
        { 0, 0, 0, 1}}}},
        /** Inverse */
     {{{{ 1/a,   0,   0,    0},
        {   0, 1/b,   0,    0},
        {   0,   0, 1/d, -e/d},
        {   0,   0,   0,    1}}}},

    };
    return M;
}

/**
 * eg. ( 90.0f, width/height, 0.1f, 100.0f)
 * Returns inverse mat
 */
inline mat4_inv GetInvPerspectiveMat( f32 FOV, f32 aspect, f32 nearPlane, f32 farPlane ) {
    f32 n = nearPlane;
    f32 f = farPlane;

    f32 a = 1.0f;
    f32 b = aspect;
    f32 c = FOV;

    f32 d = (n+f)/(n-f);
    f32 e = (2.0f*f*n)/(n-f);

    mat4_inv M = {
        /** Forward */
     {{{{ a*c, 0, 0, 0},
        { 0, b*c, 0, 0},
        { 0,   0, d, e},
        { 0,   0,-1, 0}}}},
        /** Inverse */
     {{{{ 1/(a*c),       0,   0,   0},
        {       0, 1/(b*c),   0,   0},
        {       0,       0,   0,  -1},
        {       0,       0, 1/e, d/e}}}},

    };
    return M;
}

inline mat4
Columns3x3( vec3 x, vec3 y, vec3 z) {
    mat4 M = {
        {{{ x.x, y.x, z.x, 0},
        {   x.y, y.y, z.y, 0},
        {   x.z, y.z, z.z, 0},
        {     0,   0,   0, 1}}}
    };
    return M;
}

inline mat4
Rows3x3( vec3 x, vec3 y, vec3 z) {
    mat4 M = {
        {{{ x.x, x.y, x.z, 0},
        {   y.x, y.y, y.z, 0},
        {   z.x, z.y, z.z, 0},
        {     0,   0,   0, 1}}}
    };
    return M;
}


inline vec3
GetColumn(mat4 A, u32 c)
{
    vec3 r = {{A.A[0][c], A.A[1][c], A.A[2][c]}};
    return r;
}

inline vec3
GetRow(mat4 A, u32 r)
{
    vec3 res = {{A.A[r][0], A.A[r][1], A.A[r][2]}};
    return res;
}


inline mat4_inv
CameraTransform( vec3 x, vec3 y, vec3 z, vec3 p) {
    mat4_inv result;

    mat4 A = Rows3x3( x, y, z);
    vec3 ap = -( Transform(A, Vec4( p.x, p.y, p.z, 1.0f))).xyz;
    A = Translate( A, ap);
    result.forward = A;

    vec3 ix = x / LengthSq(x);
    vec3 iy = y / LengthSq(y);
    vec3 iz = z / LengthSq(z);
    vec3 ip = {
        ap.x * ix.x + ap.y * iy.x + ap.z * iz.x,
        ap.x * ix.y + ap.y * iy.y + ap.z * iz.y,
        ap.x * ix.z + ap.y * iy.z + ap.z * iz.z
    };

    mat4 B = Columns3x3( ix, iy, iz);
    B = Translate( B, -ip);
    result.inverse = B;

    return result;
}


/* TODO(Kasper): Implement.*/
inline mat4 LookAt( vec3 cameraPosition, vec3 targetPosition, vec3 worldUpVector ) {
    mat4 M;
    return M;
}

#endif /* end of include guard: KMATH_HPP_ */
