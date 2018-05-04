/**
 *
 * Player.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */
#include "Object.h"
#include "AABB.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class kPlayer : public kObject {
    public:
    kAABB aabb;

    f32 *GetVertices( u32 &numberOfVertices ) const;
};

#endif /* end of include guard: PLAYER_H_ */
