/**
 *
 * ImageFormats.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 07/05/2018 
 */

#ifndef IMAGEFORMATS_H_JBEXPOHB
#define IMAGEFORMATS_H_JBEXPOHB

#include "Types.h"


/**
 * Gathered from: http://www.fastgraph.com/help/bmp_header_format.html
 * TODO(Kasper): Move to a separate fileformat collection -file
 */
#pragma pack(push, 1)
struct BitmapHeader_t {
    u16 type;
    u32 fileSize;
    u16 reserved1;
    u16 reserved2;
    u32 bytesToImage;
    u32 infoHeaderSize;     // must be 40 (Just kidding, apparently)
    u32 width;              // pixels
    u32 height;             // pixels
    u16 planes;             // must be 1
    u16 bitsPerPixel;       // 1,4,8,24
    u32 compression;        // 0=none, 1=RLE-8, 2=RLE-4 3=?!?! (this is what Gimp seems to put)
    u32 sizeOfImageData;    // includes padding
    u32 horizontalPPM;
    u32 verticalPPM;
    u32 numberOfColors;
    u32 numberOfImportantColors;
};
#pragma pack(pop)


#endif /* end of include guard: IMAGEFORMATS_H_JBEXPOHB */


