/**
 * Kalm2D
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#define KMATH_IMPLEMENTATION
#include "kGame2D.h"
#include "Player.cpp"
#include "Camera.cpp"
#include "Object.cpp"
#include "Scene.cpp"

/** Entry point for Kalm2D.exe to the Game64.dll */
gameExport_t * GetGameAPI( gameImport_t * system) {

    static Kalm2D engine;
    engine.system = system;
    engine.gameExport.game = &engine;
    return &engine.gameExport;
}


/**
 * Kalm2D
 */

gameImport_t * Kalm2D::system = nullptr;
gameExport_t Kalm2D::gameExport = {};


b32 Kalm2D::Initialize() {

    this->currentScene = CreateTestScene();

    return true;
}


/**
 * Main Loop
 */
i32 Kalm2D::Loop() {

    while(!this->system->commonSystem->IfWindowShouldClose()) {

        //static r64 lastTime = 0;
        //static r64 time = glfwGetTime();
        
        this->currentScene->Run();
        this->currentScene->SendRenderCommands();

        this->system->renderSystem->Draw();
        //lastTime = time;
    }
    return true;
}


void Kalm2D::Terminate() {

}


/**
 * Private
 */


void Kalm2D::SetCurrentScene( kScene *scene) {
    this->currentScene = scene;
}


void * Kalm2D::GetMemory( u32 bytes ) {
    void *memory = nullptr;
    memory = this->system->memorySystem->Alloc( bytes );
    ASSERT( memory );
    return memory;
}


/**
 * Dev function to quickly set a test scene. This should be somewhere else
 * and scenes shouldn't be loaded from C++
 */
kScene *Kalm2D::CreateTestScene() {
    kScene * scene = (kScene*)GetMemory(sizeof( kScene));
    ASSERT( scene );

    kPlayer * player = (kPlayer*)GetMemory( sizeof( kPlayer));
    kCamera * camera = (kCamera*)GetMemory( sizeof( kCamera));

    scene->player = player;
    scene->camera = camera;

    return scene;
}


/**
 * end of Kalm2D
 */
