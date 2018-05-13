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
    camera->Initialize( Vec3( 0.0f, 2.0f, 5.0f), Vec3( 0.0f, 1.0f, 0.0f));

    /** positive y is the up axis */

    scene->player = player;
    scene->camera = camera;

    kMesh_t *dragonMesh = g_System->assetSystem->LoadMesh( "Assets/Models/dragon.ply" );
    kMesh_t *cubeMesh = g_System->assetSystem->LoadMesh( "Assets/Models/cube.ply" );
    kMesh_t *barrelMesh = g_System->assetSystem->LoadMesh( "Assets/Models/barrel.ply" );
    kMesh_t *groundMesh = g_System->assetSystem->LoadMesh( "Assets/Models/plane.ply" );

    kImage_t *barrelDiffuse = g_System->assetSystem->LoadImageA( "Assets/Textures/barrel_diffuse.tga");
    kTexture_t *barrelDiffuseTexture = g_System->renderSystem->LoadTexture( barrelDiffuse);

    kImage_t *barrelSpecular = g_System->assetSystem->LoadImageA( "Assets/Textures/barrel_specular.tga");
    kTexture_t *barrelSpecularTexture = g_System->renderSystem->LoadTexture( barrelSpecular);

    vec3 dragonPositions[] = {
        Vec3( 0.0f, 0.0f, 0.0f),

        Vec3( 10.0f, 0.0f, 0.0f),
        Vec3( 0.0f, 0.0f, -10.0f),
        Vec3( -10.0f, 0.0f, 0.0f),
        Vec3( 0.0f, 0.0f, 10.0f),
        Vec3( 16.0f, 0.0f,  -24.0f)
    };

    vec3 barrelPositions[] = {
        Vec3( -7.0f, 5.0f, 8.0f),

        Vec3( 14.2f, 15.0f, 2.3f),
        Vec3( 24.2f, 10.0f, -2.3f),
        Vec3( -12.0f, 2.0f, 5.3f),
        Vec3( -17.2f, 15.0f, -12.3f),
        Vec3( 9.2f, 0.0f, 3.2f),
    };

    DiffuseMaterial dragonMaterials[6] = {};
    dragonMaterials[0].type = MaterialType_e::DIFFUSE_MATERIAL;
    dragonMaterials[0].diffuse = Vec3( 0.2f, 0.7f, 0.7f);
    dragonMaterials[0].specular = Vec3( 0.2f, 0.7f, 0.7f); dragonMaterials[0].roughness = 32.0f;
    dragonMaterials[1].type = MaterialType_e::DIFFUSE_MATERIAL;
    dragonMaterials[1].diffuse = Vec3( 0.7f, 0.2f, 0.3f);
    dragonMaterials[1].specular = Vec3( 0.7f, 0.2f, 0.3f); dragonMaterials[1].roughness = 32.0f;
    dragonMaterials[2].type = MaterialType_e::DIFFUSE_MATERIAL;
    dragonMaterials[2].diffuse = Vec3( 0.5f, 0.6f, 0.7f);
    dragonMaterials[2].specular = Vec3( 0.5f, 0.6f, 0.7f); dragonMaterials[2].roughness = 128.0f;
    dragonMaterials[3].type = MaterialType_e::DIFFUSE_MATERIAL;
    dragonMaterials[3].diffuse = Vec3( 0.4f, 0.3f, 0.7f);
    dragonMaterials[3].specular = Vec3( 0.4f, 0.3f, 0.7f); dragonMaterials[3].roughness = 24.0f;
    dragonMaterials[4].type = MaterialType_e::DIFFUSE_MATERIAL;
    dragonMaterials[4].diffuse = Vec3( 0.54f, 0.61f, 0.33f);
    dragonMaterials[4].specular = Vec3( 0.54f, 0.61f, 0.33f); dragonMaterials[4].roughness = 64.0f;
    dragonMaterials[5].type = MaterialType_e::DIFFUSE_MATERIAL;
    dragonMaterials[5].diffuse = Vec3( 0.15f, 0.15f, 0.15f);
    dragonMaterials[5].specular = Vec3( 0.15f, 0.15f, 0.15f); dragonMaterials[5].roughness = 8.0f;
/*
 *
 *    [>* Dragons <]
 *
 */
    kObject *dragonObj = (kObject*)GetMemory( sizeof( kObject ));
    *dragonObj = {};
    dragonObj->children_n = 5;
    dragonObj->scale = 20.0f;

    MeshComponent *dragonMeshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
    dragonMeshComp->mesh = dragonMesh;

    DiffuseMaterialComponent *dragonMaterialComp = (DiffuseMaterialComponent*)GetMemory( sizeof( DiffuseMaterialComponent));
    dragonMaterialComp->type = ComponentType_e::DIFFUSE_COMPONENT;
    dragonMaterialComp->material = (DiffuseMaterial*)GetMemory( sizeof( DiffuseMaterial));
    memcpy( dragonMaterialComp->material, &dragonMaterials[0], sizeof( DiffuseMaterial));

    dragonObj->components[ComponentType_e::MESH_COMPONENT] = dragonMeshComp;
    dragonObj->components[ComponentType_e::MATERIAL_COMPONENT] = dragonMaterialComp;

    dragonObj->position = dragonPositions[0];

    /** Dragon children */

    for( u32 i=0; i < dragonObj->children_n; ++i ) {
        kObject *childObj = (kObject*)GetMemory( sizeof( kObject ));
        *childObj = {};
        childObj->scale = 15.0f;

        MeshComponent *meshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
        meshComp->mesh = dragonMesh;

        DiffuseMaterialComponent *matComp = (DiffuseMaterialComponent*)GetMemory( sizeof( DiffuseMaterialComponent));
        matComp->type = ComponentType_e::DIFFUSE_COMPONENT;
        matComp->material = (DiffuseMaterial*)GetMemory( sizeof( DiffuseMaterial));
        memcpy( matComp->material, &dragonMaterials[i+1], sizeof( DiffuseMaterial));

        childObj->components[ComponentType_e::MESH_COMPONENT] = meshComp;
        childObj->components[ComponentType_e::MATERIAL_COMPONENT] = matComp;

        childObj->position = dragonPositions[i+1];

        dragonObj->children[i] = childObj;
    }

    scene->children[0] = dragonObj;
/*
 *
 *    [>* barrels <]
 *
 */
    kObject * barrelObject = (kObject*)GetMemory( sizeof( kObject));
    *barrelObject = {};
    barrelObject->children_n = 5;
    barrelObject->scale = 2.0f;
    barrelObject->position = barrelPositions[0];
    MeshComponent *barrelMeshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
    barrelMeshComp->mesh = barrelMesh;

    TextureMaterialComponent *barrelMaterialComp = (TextureMaterialComponent*)GetMemory( sizeof( TextureMaterialComponent));
    barrelMaterialComp->type = ComponentType_e::TEXTURE_COMPONENT;
    barrelMaterialComp->material = (TextureMaterial*)GetMemory( sizeof( TextureMaterial));
    barrelMaterialComp->material->type = MaterialType_e::TEXTURE_MATERIAL;

    barrelMaterialComp->material->diffuseTexture = barrelDiffuseTexture;
    barrelMaterialComp->material->specularTexture = barrelSpecularTexture;
    barrelMaterialComp->material->diffuse = Vec3( 0.6f, 0.4f, 0.0f);
    barrelMaterialComp->material->specular = Vec3( 1.0f, 1.0f, 1.0f);
    barrelMaterialComp->material->roughness = 16.0f;

    barrelObject->components[ComponentType_e::MESH_COMPONENT] = barrelMeshComp;
    barrelObject->components[ComponentType_e::MATERIAL_COMPONENT] = barrelMaterialComp;

    scene->children[1] = barrelObject;

    /** barrel children */

    for( u32 i=0; i < barrelObject->children_n; ++i ) {
        kObject *childObj = (kObject*)GetMemory( sizeof( kObject ));
        *childObj = {};
        childObj->scale = 1.1f;

        MeshComponent *meshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
        meshComp->mesh = barrelMesh;

        TextureMaterialComponent *matComp = (TextureMaterialComponent*)GetMemory( sizeof( TextureMaterialComponent));
        matComp->type = ComponentType_e::TEXTURE_COMPONENT;
        matComp->material = (TextureMaterial*)GetMemory( sizeof( TextureMaterial));
        matComp->material->type = MaterialType_e::TEXTURE_MATERIAL;
        matComp->material->diffuseTexture = barrelDiffuseTexture;
        matComp->material->specularTexture = barrelSpecularTexture;
        matComp->material->diffuse = Vec3( 1.0f);
        matComp->material->specular = Vec3( 1.0f);
        matComp->material->roughness = 16.0f;

        childObj->components[ComponentType_e::MESH_COMPONENT] = meshComp;
        childObj->components[ComponentType_e::MATERIAL_COMPONENT] = matComp;
        childObj->position = barrelPositions[i+1];

        barrelObject->children[i] = childObj;
    }
/*
 *
 *      Lights
 *
 */
    kPointLight * lightCubeObj = (kPointLight*)GetMemory( sizeof( kPointLight ));
    *lightCubeObj = {};
    lightCubeObj->scale = 0.5f;
    lightCubeObj->position = Vec3( 0.0f, 10.0f, 0.0f);
    lightCubeObj->diffuse = Vec3( 0.5f, 0.5f, 0.5f);
    lightCubeObj->ambient = Vec3( 0.2f, 0.2f, 0.2f);
    lightCubeObj->specular = Vec3( 1.0f, 1.0f, 1.0f);

    MeshComponent *cubeMeshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
    cubeMeshComp->mesh = cubeMesh;

    DiffuseMaterialComponent *cubeMatComp = (DiffuseMaterialComponent*)GetMemory( sizeof( DiffuseMaterialComponent));
    cubeMatComp->type = ComponentType_e::DIFFUSE_COMPONENT;
    cubeMatComp->material = (DiffuseMaterial*)GetMemory( sizeof( DiffuseMaterial));
    cubeMatComp->material->type = MaterialType_e::DIFFUSE_MATERIAL;
    cubeMatComp->material->diffuse = Vec3( 1.0f, 1.0f, 1.0f);
    cubeMatComp->material->specular = Vec3( 1.0f, 1.0f, 1.0f);
    cubeMatComp->material->roughness = 32.0f;

    lightCubeObj->components[ComponentType_e::MESH_COMPONENT] = cubeMeshComp;
    lightCubeObj->components[ComponentType_e::MATERIAL_COMPONENT] = cubeMatComp;

    scene->children[2] = lightCubeObj;

    /** Ground Mesh */
    kObject * groundObj = (kObject*)GetMemory( sizeof( kObject ));
    *groundObj = {};
    groundObj->scale = 50.0f;
    groundObj->position = Vec3( 0.0f, 1.0f, 0.0f);

    MeshComponent *groundMeshComp = (MeshComponent*)GetMemory( sizeof( MeshComponent));
    groundMeshComp->mesh = groundMesh;

    DiffuseMaterialComponent *groundMatComp = (DiffuseMaterialComponent*)GetMemory( sizeof( DiffuseMaterialComponent));
    groundMatComp->type = ComponentType_e::DIFFUSE_COMPONENT;
    groundMatComp->material = (DiffuseMaterial*)GetMemory( sizeof( DiffuseMaterial));
    groundMatComp->material->type = MaterialType_e::DIFFUSE_MATERIAL;

    groundMatComp->material->diffuse = Vec3( 0.1f, 0.3f, 0.1f);
    groundMatComp->material->specular = Vec3( 1.0f, 1.0f, 1.0f);
    groundMatComp->material->roughness = 64.0f;

    groundObj->components[ ComponentType_e::MESH_COMPONENT] = groundMeshComp;
    groundObj->components[ ComponentType_e::MATERIAL_COMPONENT] = groundMatComp;

    scene->children[3] = groundObj;

    scene->children_n = 4;

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
