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

/** used as indices */
enum ComponentType_e {
    NO_TYPE = -1,
    MESH_COMPONENT,
    MATERIAL_COMPONENT,
    MOVER_COMPONENT,
    COMPONENTS_N
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


class MaterialComponent : public kComponent {
    public:
    ComponentType_e type = MATERIAL_COMPONENT;

    kMaterial_t material = {};
};

#endif /* end of include guard: COMPONENT_H_ */
