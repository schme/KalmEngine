/**
 *
 * Systems.h
 *
 * File that holds all the platform layer interfaces for exporting
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */



#ifndef SYSTEMS_H_
#define SYSTEMS_H_


#include "kalm_shared.h"

class CommonSystem {
    public:
    virtual b32     IfWindowShouldClose() const =0;
};

class FileSystem {
    public:
    virtual i32     ReadWholeFile( const char *filename, const u32 buffer_size, void *buffer ) const =0;
    virtual i32     WriteWholeFile( const char *filename, const u32 buffer_size, const void *buffer) const =0;
    virtual b32     GetWholeFileSize( const char *filename, u64 *file_size ) const =0;
};

class MemorySystem {
    public:
    typedef u64     Marker;
    virtual void *  Alloc( u32 size_bytes ) =0;
    virtual void *  AllocAligned( u32 size_bytes, u32 alignment ) =0;
    virtual void    Free( Marker mark ) =0;
};

class RenderSystem {
    public:
    virtual void    Draw() const =0;
};

class AssetSystem {
    public:
        virtual kImage_t *GetImage(const char *filename) const =0;
        virtual kScene_t *LoadScene() const =0;
};

#endif /* end of include guard: SYSTEMS_H_ */
