/**
 *
 * Scene.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018 
 */

#include "Scene.h"

void kScene::Run() {
    this->player->Run();
    this->camera->Run();
}

void kScene::SendRenderCommands() {
    this->player->SendRenderCommands();
    this->camera->SendRenderCommands();
}

kPlayer& kScene::GetPlayer() const {
    return *this->player;
}

kCamera& kScene::GetCamera() const {
    return *this->camera;
}

void kScene::SetPlayer( kPlayer *newPlayer) {
    this->player = newPlayer;
}

void kScene::SetCamera( kCamera *newCamera) {
    this->camera = newCamera;
}
