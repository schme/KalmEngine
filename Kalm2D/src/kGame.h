/**
 *
 * kGame Interface
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include "kalm_shared.h"
#include "Memory.h"

struct gameImport_t;
struct gameExport_t;

const char * title = "Kalm2D";

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
};
