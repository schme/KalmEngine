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
    vec3 color = {};
};


class kLightCube : public kLight {
};



#endif /* end of include guard: LIGHT_H_LMH3TAZ4 */
