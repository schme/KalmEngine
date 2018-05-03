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

class kScene {
    public:
    void Run();
    void Render();
    private:
    kPlayer player;

    kPlayer GetPlayer() const;
};


#endif /* end of include guard: KSCENE_H_ */
