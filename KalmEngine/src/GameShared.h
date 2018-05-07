/**
 *
 * GameShared.h
 *
 * Stuff that can be passed around globally inside the Game dll files for easier
 * access to subsystems etc.
 * Sys_Shared.h is the equivalent for the System side
 *
 * This isn't too good design, but makes the development process easier for now.
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 07/05/2018 
 */

#ifndef GAMESHARED_H_DKTHUNPY
#define GAMESHARED_H_DKTHUNPY

#include "KalmGame.h"

static gameImport_t *g_System = nullptr;


static inline void * GetMemory( u32 bytes ) {
    void *memory = nullptr;
    memory = g_System->memorySystem->Alloc( bytes );
    ASSERT( memory );
    return memory;
}

#endif /* end of include guard: GAMESHARED_H_DKTHUNPY */
