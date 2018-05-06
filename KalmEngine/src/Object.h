/**
 *
 * Object.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "kVector.h"
#include "KalmTypes.h"

class kObject {
    public:
    vec3 position = {};

    void Run() {}

    vertices_t* GetVertices() const {
        return nullptr;
    }
};


class kCube : kObject {
    vertices_t* GetVertices() const {
        return nullptr;
    }
};

#endif /* end of include guard: OBJECT_H_ */
