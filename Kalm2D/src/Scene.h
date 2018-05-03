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
class kScene {
    public:
    kPlayer *player;
    kCamera *camera;

    void Run();
    void SendRenderCommands();

    kPlayer& GetPlayer() const;
    kCamera& GetCamera() const;
    void SetPlayer( kPlayer *newPlayer );
    void SetCamera( kCamera *newCamera );

    private:
};


#endif /* end of include guard: KSCENE_H_ */
