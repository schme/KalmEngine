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
 * TODO(Kasper): Make indices byte-sized to reduce GPU memory cost?
 */
struct kMesh_t {
    b32 hasVertices = 0;
    b32 hasNormals = 0;
    b32 hasTexcoords = 0;
    b32 hasColors = 0;
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

struct renderType_t {
    i32 vertexArrayIndex = -1;
    i32 vertexBufferIndex = -1;
    i32 shaderIndex = -1;
};

struct kMaterial_t {
    vec3 color = Vec3(1.0f, 0.0f, 1.0f);
    f32 roughness = 32.0f;
};


#endif /* end of include guard: KALMTYPES_H_ */
