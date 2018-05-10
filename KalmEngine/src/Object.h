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
    vec3 velocity = {};
    f32 scale = 1.0f;

    /* TODO(Kasper): make dynamic?*/
    kObject *children[DEBUG_OBJ_MAX_CHILDREN] = {};
    u32 children_n = 0;

    /* TODO(Kasper): make dynamic?*/
    kComponent *components[DEBUG_OBJ_MAX_COMPONENTS] = {};

    /** recursive */
    void Input( const f32 deltaTime ) {
        for (u32 i = 0; i < this->children_n; ++i) {
            kObject *child = this->children[i];
            if( child ) {
                child->Input( deltaTime );
            }
        }
    }

    /** recursive */
    void Update() {
        for (u32 i = 0; i < this->children_n; ++i) {
            kObject *child = this->children[i];
            if( child ) {
                this->children[i]->Update();
            }
        }
    }

    /** recursive */
    void Update( const f32 deltaTime ) {
        for (u32 i = 0; i < this->children_n; ++i) {
            kObject *child = this->children[i];
            if( child ) {
                this->children[i]->Update( deltaTime );
            }
        }
    }
};


#endif /* end of include guard: OBJECT_H_ */
