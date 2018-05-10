/**
 * KalmGame
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include "KalmGame.h"
#include "GameShared.h"
#include "AABB.cpp"
#include "Player.cpp"
#include "Camera.cpp"
#include "Object.cpp"
#include "Scene.cpp"

/** Entry point for KalmGame.exe to the Game64.dll */
gameExport_t * GetGameAPI( gameImport_t * system) {

    static KalmGame engine;
    g_System = system;
    engine.gameExport.game = &engine;
    return &engine.gameExport;
}


/**
 * KalmGame
 */
gameExport_t KalmGame::gameExport = {};

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
    *player = {};
    camera->Initialize( Vec3( 0.0f, 0.0f, 0.0f), Vec3( 0.0f, 1.0f, 0.0f));

    /** positive y is the up axis */

    scene->player = player;
    scene->camera = camera;

    kMesh_t *mesh = g_System->assetSystem->LoadMesh( "Assets/Models/dragon_vrip_res4.ply" );
    //kMesh_t *mesh = g_System->assetSystem->LoadMesh( "Assets/Models/bunny.ply" );

    vec3 testPositions[] = {
        Vec3( 0.0f, 0.0f, 0.0f),
        Vec3( 0.2f, 2.1f, 2.0f),
        Vec3( 3.2f, 3.1f, 5.0f),
        Vec3( -2.2f, -1.1f, 2.0f),
        Vec3( -4.2f, 0.1f, -2.0f)
    };

    for( int i=0; i < DEBUG_OBJ_MAX_CHILDREN; ++i ) {
        kObject *obj = (kObject*)GetMemory( sizeof( kObject ));
        MeshComponent *meshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
        meshComp->mesh = mesh;
        obj->components[0] = meshComp;
        obj->position = testPositions[i];
        scene->objects[i] = obj;
    }

    return scene;
}

void KalmGame::LoadTestScene( kScene_t *scene) {
    g_System->renderSystem->LoadTestScene( scene );
}

void KalmGame::LoadScene( kScene_t *scene ) {
}

void KalmGame::RunCurrentScene( const f32 deltaTime ) {
    /** Run Logic on Objects */
    //TODO(Kasper): HARD CODED CHILD VALUE

    currentScene->camera->Update( deltaTime);
    currentScene->player->Update( deltaTime);
    for( int i=0; i < DEBUG_OBJ_MAX_CHILDREN; i++) {
        currentScene->objects[i]->Update( deltaTime );
    }
}

void KalmGame::RenderCurrentScene( const f32 deltaTime) {
    /** Setup per-frame modifications */

}


b32 KalmGame::Initialize() {

    return true;
}


/**
 * Main Loop
 */
i32 KalmGame::Loop() {

    kScene_t *testScene = this->CreateTestScene();
    this->SetCurrentScene( testScene );
    this->LoadTestScene( testScene);
    static f32 deltaTime = 0;
    static f64 lastTime = 0;
    static f64 time = 0;

    while(!g_System->commonSystem->IfWindowShouldClose()) {

        time = g_System->commonSystem->GetTime();

        deltaTime = (f32)(time - lastTime);

        //printf( "deltaTime: %f\n", deltaTime);


        /** Get input */
        HandleInput( deltaTime );

        /** Update objects */
        RunCurrentScene( deltaTime );

        RenderCurrentScene( deltaTime );

        g_System->renderSystem->DrawTestScene( currentScene);

        g_System->commonSystem->PollEvents();
        lastTime = time;
    }
    return true;
}


void KalmGame::Terminate() {

}


/**
 * Private
 */


void KalmGame::HandleInput( const f32 deltaTime) {

    currentScene->camera->Input( deltaTime);
    currentScene->player->Input( deltaTime);

    for( int i=0; i < DEBUG_OBJ_MAX_CHILDREN; i++) {
        currentScene->objects[i]->Input( deltaTime);
    }

    g_System->commonSystem->SwapAndClearState();
}

void KalmGame::SetCurrentScene( kScene_t *scene) {
    this->currentScene = scene;
}




/**
 * end of KalmGame
 */
