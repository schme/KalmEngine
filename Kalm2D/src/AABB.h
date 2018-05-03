#ifndef AABB_H_
#define AABB_H_

#include "kVector.h"
#include "Component.h"

class kAABB : kComponent {
public:
    vec3 center;
    vec3 half;
};

#endif /* AABB_H_ */
