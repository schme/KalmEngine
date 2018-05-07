/**
 *
 * Component.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "KalmTypes.h"

enum ComponentType_e {
    NO_TYPE,
    MESH_COMPONENT
};

class kComponent {
    public:
    ComponentType_e type = {};
};


class MeshComponent : public kComponent {
    public:
    ComponentType_e type = MESH_COMPONENT;
    kMesh_t *mesh = {};
};

#endif /* end of include guard: COMPONENT_H_ */
