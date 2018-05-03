/**
 *
 * Object.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018 
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "kMath.hpp"

class kObject {
    public:
    vec3 position;

    void Run() {}
    void SendRenderCommands() {}
};



#endif /* end of include guard: OBJECT_H_ */
