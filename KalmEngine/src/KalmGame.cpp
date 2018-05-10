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
#include "Light.cpp"

#include "Sys_Config.h"

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
    *camera = {};
    camera->Initialize( Vec3( 0.0f, 0.0f, 5.0f), Vec3( 0.0f, 1.0f, 0.0f));

    /** positive y is the up axis */

    scene->player = player;
    scene->camera = camera;

    kMesh_t *dragonMesh = g_System->assetSystem->LoadMesh( "Assets/Models/dragon_vrip_res4.ply" );
    kMesh_t *cubeMesh = g_System->assetSystem->LoadMesh( "Assets/Models/cube.ply" );
    kMesh_t *d20Mesh = g_System->assetSystem->LoadMesh( "Assets/Models/icosahedron_ascii.ply" );

    vec3 dragonPositions[] = {
        Vec3( 0.0f, 0.0f, 0.0f),
        Vec3( 10.0f, 0.0f, 0.0f),
        Vec3( 0.0f, 0.0f, -10.0f),
        Vec3( -10.0f, 0.0f, 0.0f),
        Vec3( 0.0f, 0.0f, 10.0f),
        Vec3( 16.0f, 0.0f,  -24.0f)
    };

    vec3 d20Positions[] = {
        Vec3( -7.0f, 5.0f, 8.0f),
        Vec3( 14.2f, 15.0f, 2.3f),
        Vec3( 24.2f, 10.0f, -2.3f),
        Vec3( -12.0f, 2.0f, 5.3f),
        Vec3( -17.2f, 15.0f, -12.3f),
    };

    kObject *dragonObj = (kObject*)GetMemory( sizeof( kObject ));
    *dragonObj = {};
    dragonObj->children_n = 5;
    dragonObj->scale = 20.0f;
    MeshComponent *dragonMeshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
    dragonMeshComp->mesh = dragonMesh;
    dragonObj->components[0] = dragonMeshComp;
    dragonObj->position = dragonPositions[0];

    for( u32 i=0; i < dragonObj->children_n; ++i ) {
        kObject *childObj = (kObject*)GetMemory( sizeof( kObject ));
        *childObj = {};
        childObj->scale = 10.0f;
        MeshComponent *meshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
        meshComp->mesh = dragonMesh;
        childObj->components[0] = meshComp;
        childObj->position = dragonPositions[i+1];

        dragonObj->children[i] = childObj;
    }

    scene->children[0] = dragonObj;

    kObject * d20Object = (kObject*)GetMemory( sizeof( kObject));
    *d20Object = {};
    d20Object->children_n = 3;
    d20Object->scale = 2.0f;
    d20Object->position = d20Positions[0];
    MeshComponent *d20MeshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
    d20MeshComp->mesh = d20Mesh;
    d20Object->components[0] = d20MeshComp;
    scene->children[1] = d20Object;

    for( u32 i=0; i < d20Object->children_n; ++i ) {
        kObject *childObj = (kObject*)GetMemory( sizeof( kObject ));
        *childObj = {};
        childObj->scale = 1.0f;
        MeshComponent *meshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
        meshComp->mesh = d20Mesh;
        childObj->components[0] = meshComp;
        childObj->position = d20Positions[i+1];

        d20Object->children[i] = childObj;
    }

    kLightCube * lightCubeObj = (kLightCube*)GetMemory( sizeof( kObject ));
    *lightCubeObj = {};
    lightCubeObj->scale = 1.0f;
    lightCubeObj->position = Vec3( 0.0f, 10.0f, 0.0f);
    MeshComponent *cubeMeshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
    cubeMeshComp->mesh = cubeMesh;
    lightCubeObj->components[0] = cubeMeshComp;
    scene->children[2] = lightCubeObj;

    scene->children_n = 3;

    return scene;
}

void KalmGame::LoadTestScene( kScene_t *scene) {
    g_System->renderSystem->LoadTestScene( scene );
}

void KalmGame::LoadScene( kScene_t *scene ) {
}

void KalmGame::RunCurrentScene( const f32 deltaTime ) {
    /** Run Logic on Objects */

    currentScene->camera->Update( deltaTime);
    currentScene->player->Update( deltaTime);
    for( u32 i=0; i < currentScene->children_n; i++) {
        currentScene->children[i]->Update( deltaTime );
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

    ((kConfig*)g_System->configSystem->Get())->Input( GetGameInput() );

    currentScene->camera->Input( deltaTime);
    currentScene->player->Input( deltaTime);

    for( u32 i=0; i < currentScene->children_n; i++) {
        currentScene->children[i]->Input( deltaTime);
    }

    g_System->commonSystem->SwapAndClearState();
}

void KalmGame::SetCurrentScene( kScene_t *scene) {
    this->currentScene = scene;
}




/**
 * end of KalmGame
 */
