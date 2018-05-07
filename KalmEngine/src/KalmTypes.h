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
#include "kVector.h"
#include "Shader.h"

/**
 * A struct for storing vertices in a way OpenGL can
 * easily consume them up
 */
struct kMesh_t {
    b32 hasVertices = 0;
    b32 hasNormals = 0;
    b32 hasTexcoords = 0;
    u32 vertices_n;
    u32 indices_n;
    f32 *vertices;
    u32 *indices;
};

/**
 * A loaded image to pass around
 */
struct kImage_t {
    u16 width;
    u16 height;
    u32 reserved;
    u64 assetMark;
    u64 bufferSize;
    const char *filename;
    void *imageBuffer;
};

struct kTexture_t {
    u32 ID;
    kImage_t *image;
};

struct renderBufferGroup_t {
    u32 ID;
    Shader shader;
    mat4 modelView;
    kMesh_t *groupVerts;
};

#endif /* end of include guard: KALMTYPES_H_ */
