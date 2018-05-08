/**
 *
 * kGame  Interface
 *
 * Shared for the Sys_Kalm module
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#ifndef KALMSHARED_H_
#define KALMSHARED_H_

#include "Systems.h"
#include "Types.h"

const u32 frameBufferWidth = 1280;
const u32 frameBufferHeight = 720;

struct gameImport_t;
struct gameExport_t;

class kGame {
    public:
    virtual b32 Initialize() = 0;
    virtual i32 Loop () = 0;
    virtual void Terminate() = 0;
};

extern "C"
gameExport_t * GetGameAPI( gameImport_t * system);

struct gameExport_t {
    kGame *game;
};

struct gameImport_t {
    i32                     version;        /** not actually used, but Doom3 did so I need to! */
    CommonSystem *          commonSystem;
    MemorySystem *          memorySystem;
    FileSystem *            fileSystem;
    RenderSystem *          renderSystem;
    AssetSystem *           assetSystem;
};


struct gameButtonState_t {
    s32 toggleCount;
    b32 endedDown;
};

struct mouseInput_t {
    f32 posx;
    f32 posy;
    gameButtonState_t right;
    gameButtonState_t left;
};


struct gameInput_t {
    mouseInput_t mouseInput;

    gameButtonState_t up;
    gameButtonState_t left;
    gameButtonState_t right;
    gameButtonState_t down;

    gameButtonState_t actionQ;
    gameButtonState_t actionE;
    gameButtonState_t actionR;
    gameButtonState_t actionF;
    gameButtonState_t actionSpace;
    gameButtonState_t actionEnter;
    gameButtonState_t actionEsc;
    gameButtonState_t action0;
    gameButtonState_t action1;
    gameButtonState_t action2;
    gameButtonState_t action3;
    gameButtonState_t action4;
    gameButtonState_t action5;
    gameButtonState_t action6;
    gameButtonState_t action7;
    gameButtonState_t action8;
    gameButtonState_t action9;
};

#endif /* end of include guard: KALMSHARED_H_ */
