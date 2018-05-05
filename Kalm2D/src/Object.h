/**
 *
 * Object.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018 
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "kMath.h"

struct vertsAndIndices_t {
    u32 vertices_n;
    u32 indices_n;
    f32 *vertices;
    u32 *indices;
};


class kObject {
    public:
    vec3 position = {};

    void Run() {}

    vertsAndIndices_t* GetVertices() const {
        return nullptr;
    }
};


class kCube : kObject {
    vertsAndIndices_t* GetVertices() const {
        return nullptr;
    }
};

#endif /* end of include guard: OBJECT_H_ */
