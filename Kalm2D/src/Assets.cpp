/**
 *
 * Assets.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Assets.h"

/**
 * Currently supports only BMP files
 */
kImage_t* kAssets::GetImage( const char *filename) const {
    u64 fileSize = 0;
    if( ! g_Filesystem->GetWholeFileSize( filename, &fileSize) || fileSize == 0) {
        printf("Getting file size from: %s failed, or fileSize was 0\n", filename);
        return nullptr;
    }
    // TODO(Kasper): Allocate memory for the filebuffer from the memory system instead */
    void * fileBuffer = std::malloc( fileSize);
    if( ! fileBuffer ) {
        PRINTL_STR( "Could not receive filebuffer");
    }
    if( ! g_Filesystem->ReadWholeFile( filename, (u32)fileSize, fileBuffer)) {
        printf("kAssets: Reading file: %s (filesize: %llu) to buffer failed\n", filename, fileSize);
        return nullptr;
    }
    kImage_t *imageObject = LoadBMPFile(filename, fileBuffer);
    if( !imageObject) {
        PRINTL_STR( "Loading image file failed.");
    }

    return imageObject;
}


/**
 * TODO(Kasper): Widen functionality (read additional types of BMP)
 *
 * Returns the image object
 */
kImage_t* kAssets::LoadBMPFile( const char * filename, const void *filebuffer) const {
    BitmapHeader_t header = *((BitmapHeader_t*)filebuffer);

    //TODO(Kasper): Check compression
    if( header.type != 0x4D42)  {  // "BM"
        PRINT_STR("Tried to read a non BMP file as BMP, or the BMP type is not recognized: ");
        PRINTL_STR( filename );
    }
    kImage_t *imageObject = (kImage_t*)g_Memory->Alloc( sizeof( kImage_t));
    imageObject->assetMark = g_Memory->GetMarker();
    imageObject->width = safeCastU32ToU16( header.width);
    imageObject->height = safeCastU32ToU16( header.height);
    imageObject->bufferSize = header.sizeOfImageData;
    imageObject->imageBuffer = g_Memory->AllocAligned( header.sizeOfImageData, header.bitsPerPixel);

    void *startOfImage = (u8*)filebuffer + header.bytesToImage;
    std::memcpy( imageObject->imageBuffer, startOfImage, header.sizeOfImageData);

    return imageObject;
}
