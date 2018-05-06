/**
 *
 * GameTypes.h
 *
 * A collection of data types, structures, classes and methods used 
 * for communication between the modules.
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 06/05/2018 
 */
#ifndef KALMTYPES_H_
#define KALMTYPES_H_

#include "Types.h"

struct vertsAndIndices_t {
    u32 vertices_n;
    u32 texcoords_n;
    u32 indices_n;
    f32 *vertices;
    f32 *texcoords;
    u32 *indices;
};

struct kImage_t {
    u16 width;
    u16 height;
    u32 reserved;
    u64 assetMark;
    u64 bufferSize;
    const char *filename;
    void *imageBuffer;
};


#endif /* end of include guard: KALMTYPES_H_ */
