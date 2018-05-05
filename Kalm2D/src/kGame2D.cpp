/**
 * Kalm2D
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include "kGame2D.h"
#include "AABB.cpp"
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


void Kalm2D::RunCurrentScene() {
    /** Run Logic on Objects */
}

void Kalm2D::RenderCurrentScene() {
    /** Setup per-frame modifications */

    mat4 model = RotationX( Radians(-55.0f));
    //mat4 model = RotationY( glm::radians(-55.0f)) * RotationZ( glm::radians(-55.0f));
    mat4 view = Transpose(Translate( Vec3( 0.0f, 0.0f, -3.0f)));
    mat4 modelView = model * view;
    this->system->renderSystem->SetGroupModelView( modelView );
}


b32 Kalm2D::Initialize() {

    mat4 perspective = GetPerspectiveMat( 60.0f, (f32)frameBufferWidth / (f32)frameBufferHeight, 0.1f, 100.0f);
    this->system->renderSystem->SetPerspective( perspective );
    this->currentScene = CreateTestScene();

    return true;
}


/**
 * Main Loop
 */
i32 Kalm2D::Loop() {


    this->system->assetSystem->LoadScene( this->currentScene );

    while(!this->system->commonSystem->IfWindowShouldClose()) {

        static r64 lastTime = 0;
        static r64 time = this->system->commonSystem->GetTime();

        /** Get input */

        RunCurrentScene();
        RenderCurrentScene();

        this->system->renderSystem->Draw();

        lastTime = time;
    }
    return true;
}


void Kalm2D::Terminate() {

}


/**
 * Private
 */


void Kalm2D::SetCurrentScene( kScene_t *scene) {
    this->currentScene = scene;
}


void * Kalm2D::GetMemory( u32 bytes ) {
    void *memory = nullptr;
    memory = Kalm2D::system->memorySystem->Alloc( bytes );
    ASSERT( memory );
    return memory;
}


/**
 * Dev function to quickly set a test scene. This should be somewhere else
 * and scenes shouldn't be loaded from C++, but created scripts presumably
 */
kScene_t * Kalm2D::CreateTestScene() {
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
 * end of Kalm2D
 */
