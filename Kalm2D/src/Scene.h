/**
 *
 * Scene.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#ifndef KSCENE_H_
#define KSCENE_H_

#include "Player.h"
#include "Camera.h"


/**
 * kScene
 *
 * All scene objects have a camera and a player
 */
struct kScene_t {
    public:
    u32 ID;
    kPlayer *player;
    kCamera *camera;

    private:
};

#endif /* end of include guard: KSCENE_H_ */
