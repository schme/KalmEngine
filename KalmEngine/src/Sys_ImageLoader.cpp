/**
 *
 * Sys_ImageLoader.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 07/05/2018 
 */

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION

#include "kcl.hpp"
#include "Sys_Shared.h"
#include "Sys_ImageLoader.h"

kImage_t* ImageLoader::LoadImage( const char *filename ) const {

    s32 width, height, channels;
    unsigned char *data = stbi_load( filename, &width, &height, &channels, 0);
    ASSERT(data);

    kImage_t* result = (kImage_t*)g_Memory->Alloc( sizeof( kImage_t));
    result->width = (u16)width;
    result->height = (u16)height;
    u32 bufferSize = width * height * channels * sizeof(f32);
    result->bufferSize = bufferSize;

    result->imageBuffer = g_Memory->Alloc( bufferSize );

    memcpy( result->imageBuffer, data, result->bufferSize);

    stbi_image_free(data);

    return result;
}
