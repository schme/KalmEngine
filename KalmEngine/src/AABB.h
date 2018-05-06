#ifndef AABB_H_
#define AABB_H_

#include "kVector.h"
#include "Component.h"
#include "kcl.hpp"

class kAABB : kComponent {
public:
    vec3 center;
    vec3 half;
    vec3 GetCorner( const u32 i ) const;
};

#endif /* AABB_H_ */
