/**
 *
 * kLight
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 10/05/2018
 */


#ifndef LIGHT_H_LMH3TAZ4
#define LIGHT_H_LMH3TAZ4

#include "Object.h"

class kLight : public kObject {
    public:
    vec3 diffuse = {};
    vec3 ambient = {};
    vec3 specular = {};
};

class kPointLight : public kLight {
    public:
};


class kLightCube : public kLight {
    public:
};



#endif /* end of include guard: LIGHT_H_LMH3TAZ4 */
