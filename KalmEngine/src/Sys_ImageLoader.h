/**
 *
 * Sys_ImageLoader.h
 *
 * Uses stb_image to load images
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 07/05/2018
 */

#ifndef SYS_IMAGELOADER_H_LCSEMRZO
#define SYS_IMAGELOADER_H_LCSEMRZO

#include "KalmTypes.h"
#include "ImageFormats.h"

class ImageLoader {
    public:
    kImage_t* LoadImage( const char *filename ) const;
};

#endif /* end of include guard: SYS_IMAGELOADER_H_LCSEMRZO */
