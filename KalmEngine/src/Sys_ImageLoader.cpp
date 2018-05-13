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

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load( filename, &width, &height, &channels, 4);
    ASSERT(data);

    kImage_t* result = (kImage_t*)g_Memory->Alloc( sizeof( kImage_t));
    ASSERT( result);
    *result = {};
    result->width = (u16)width;
    result->height = (u16)height;
    u32 bufferSize = width * height * channels;
    result->bufferSize = bufferSize;

    result->imageBuffer = g_Memory->Alloc( bufferSize );
    result->filename = filename;

    std::memcpy( result->imageBuffer, data, result->bufferSize);

    stbi_image_free(data);

    return result;
}
