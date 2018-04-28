/**
 * Kalm2D
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include "kGame2D.h"

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

    /** Memory */

    /** Filesystem */


    /** TODO(Kasper): Testing image loading */

    const char *filename = "Assets/Sprites/ram.bmp";
    u64 file_size = 0;
    this->system->fileSystem->GetWholeFileSize( filename, &file_size );
    PRINT_STR( "file_size: "); printf("%lluKb\n", file_size/1024);
    void * fileBuffer = this->system->memorySystem->Alloc( (u32)file_size );
    if(! this->system->fileSystem->ReadWholeFile( filename, (u32)file_size, fileBuffer )) {
        PRINT_STR( "FAIL load file ");
        PRINTL_STR( filename);
    } else {
        PRINT_STR( "SUCCESS load file ");
        PRINTL_STR( filename);
    }

    return true;
}


/**
 * Main Loop
 */
i32 Kalm2D::Loop() {

    while(!this->system->commonSystem->IfWindowShouldClose()) {

        //static r64 lastTime = 0;
        //static r64 time = glfwGetTime();

        this->system->renderSystem->Draw();

        //lastTime = time;
    }

    return true;
}


void Kalm2D::Terminate() {

}

/**
 * end of Kalm2D
 */


