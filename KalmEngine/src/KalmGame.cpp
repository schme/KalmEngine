/**
 * KalmGame
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include "KalmGame.h"
#include "AABB.cpp"
#include "Player.cpp"
#include "Camera.cpp"
#include "Object.cpp"
#include "Scene.cpp"

/** Entry point for KalmGame.exe to the Game64.dll */
gameExport_t * GetGameAPI( gameImport_t * system) {

    static KalmGame engine;
    engine.system = system;
    engine.gameExport.game = &engine;
    return &engine.gameExport;
}


/**
 * KalmGame
 */

gameImport_t * KalmGame::system = nullptr;
gameExport_t KalmGame::gameExport = {};


void KalmGame::RunCurrentScene() {
    /** Run Logic on Objects */
}

void KalmGame::RenderCurrentScene() {
    /** Setup per-frame modifications */

}


b32 KalmGame::Initialize() {

    return true;
}


/**
 * Main Loop
 */
i32 KalmGame::Loop() {


    while(!this->system->commonSystem->IfWindowShouldClose()) {

        static r64 lastTime = 0;
        static r64 time = this->system->commonSystem->GetTime();

        /** Get input */

        RunCurrentScene();
        RenderCurrentScene();

        this->system->renderSystem->Draw();
        this->system->commonSystem->PollEvents();

        lastTime = time;
    }
    return true;
}


void KalmGame::Terminate() {

}


/**
 * Private
 */


void KalmGame::SetCurrentScene( kScene_t *scene) {
    this->currentScene = scene;
}


void * KalmGame::GetMemory( u32 bytes ) {
    void *memory = nullptr;
    memory = KalmGame::system->memorySystem->Alloc( bytes );
    ASSERT( memory );
    return memory;
}


/**
 * Dev function to quickly set a test scene. This should be somewhere else
 * and scenes shouldn't be loaded from C++, but created scripts presumably
 */
kScene_t * KalmGame::CreateTestScene() {
    kScene_t * scene = (kScene_t*)GetMemory(sizeof( kScene_t));
    ASSERT( scene );

    scene->ID = 0;

    kPlayer * player = (kPlayer*)GetMemory( sizeof( kPlayer));
    kCamera * camera = (kCamera*)GetMemory( sizeof( kCamera));

    player->position = {};
    player->aabb.center = player->position;
    player->aabb.half = Vec3( 1.0f);
    camera->position = Vec3( 0.0f, 0.0f, 3.0f);
    camera->targetPosition = player->position;
    /** positive y is the up axis */

    scene->player = player;
    scene->camera = camera;

    return scene;
}


/**
 * end of KalmGame
 */
