/**
 *
 * Player.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Systems.h"
#include "Object.h"
#include "AABB.h"

class kPlayer : public kObject {
    public:
    kAABB aabb;
};

#endif /* end of include guard: PLAYER_H_ */
