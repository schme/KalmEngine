/**
 *
 * kGame Interface
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
    i32                     version;
    CommonSystem *          commonSystem;
    MemorySystem *          memorySystem;
    FileSystem *            fileSystem;
    RenderSystem *          renderSystem;
    AssetSystem *           assetSystem;
};

#endif /* end of include guard: KALMSHARED_H_ */