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
#include "Component.h"

class kObject {
    public:
    vec3 position = {};

    /* TODO(Kasper): make dynamic*/
    kObject *children[5] = {};

    /* TODO(Kasper): make dynamic*/
    kComponent *components[5] = {};

    void Run() {}
};


#endif /* end of include guard: OBJECT_H_ */
