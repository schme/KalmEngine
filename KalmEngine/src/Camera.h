/**
 *
 * Camera.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Object.h"

class kCamera : public kObject {
    public:
    vec3 position;
    vec3 targetPosition;
};

#endif /* end of include guard: CAMERA_H_ */
