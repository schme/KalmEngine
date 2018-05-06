/**
 *
 * Camera.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */
#include "Object.h"

#ifndef CAMERA_H_
#define CAMERA_H_

class kCamera : public kObject {
    public:
    vec3 position;
    vec3 targetPosition;
};

#endif /* end of include guard: CAMERA_H_ */