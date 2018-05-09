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

#define DEBUG_OBJ_MAX_CHILDREN 5
#define DEBUG_OBJ_MAX_COMPONENTS 5

class kObject {
    public:
    vec3 position = {};

    /* TODO(Kasper): make dynamic?*/
    kObject *children[DEBUG_OBJ_MAX_CHILDREN] = {};

    /* TODO(Kasper): make dynamic?*/
    kComponent *components[DEBUG_OBJ_MAX_COMPONENTS] = {};

    /** recursive */
    void Update() {
        for (int i = 0; i < DEBUG_OBJ_MAX_CHILDREN; ++i) {
            kObject *child = this->children[i];
            if( child ) {
                this->children[i]->Update();
            }
        }
    }

    /** recursive */
    void Update( f32 deltaTime ) {
        for (int i = 0; i < DEBUG_OBJ_MAX_CHILDREN; ++i) {
            kObject *child = this->children[i];
            if( child ) {
                this->children[i]->Update( deltaTime );
            }
        }
    }
};


#endif /* end of include guard: OBJECT_H_ */
