/**
 *
 * Assets.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Assets.h"

renderBufferGroup_t renderGroups[1];

void kAssets::LoadScene( kScene_t *scene) const {
    /** compile and store shaders */
    /** create vertice group */
    CreateVerticeGroups( scene);

    /** create intermediate render commands */
}

void kAssets::CreateVerticeGroups( kScene_t *scene) const {
    renderBufferGroup_t group = {};
    group.ID = 0;
    group.vertices = scene->player->GetVertices( group.numberOfVertices);
    group.shaderID = 0;

    renderGroups[ group.ID] = group;
}

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

    std::free( fileBuffer);
    return imageObject;
}


/**
 * TODO(Kasper): Widen functionality (read additional types of BMP)
 *
 * Returns the image object
 */
kImage_t* kAssets::LoadBMPFile( const char * filename, const void *filebuffer) const {
    BitmapHeader_t header = *((BitmapHeader_t*)filebuffer);

    /** gimp seems to give compression value 3, and that apparently means no compression, so check only
     * for the 2 different compression types we know we can't handle, RLE-8 and RLE-4.
     * We'll shoot ourselves in the foot later! */
    if( header.type != 0x4D42 && header.compression != 1 && header.compression != 2 )  {  // "BM"
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

    /** Here we assume an ABGR format (0xRRGGBBAA), which can't be used in core OpenGL, so we swizzle them 
     *  to RGBA (0xAABBGGRR) */

    //TODO(Kasper): This is starting to become a bit sketchy, even for me. Can we get the color masks at least
    // from the headers?
    u32 alphaMask = 0x000000FF;
    u32 blueMask = 0x0000FF00;
    u32 greenMask = 0x00FF0000;
    u32 redMask = 0xFF000000;

    u32 *ptr_i = (u32*)startOfImage;
    u32 *ptr_j = (u32*)(imageObject->imageBuffer);

    for (u32 i = 0; i < header.sizeOfImageData / 4; ++i) {
        u32 swizzledColor = {};

        u32 redByte = (*ptr_i) & redMask;
        u32 greenByte = (*ptr_i) & greenMask;
        u32 blueByte = (*ptr_i) & blueMask;
        u32 alphaByte = (*ptr_i) & alphaMask;

        swizzledColor = ( redByte >> 24) |
                        ( greenByte >> 8) |
                        ( blueByte << 8) |
                        ( alphaByte << 24);

        *ptr_j++ = swizzledColor;
        ptr_i++;
    }

    return imageObject;
}
