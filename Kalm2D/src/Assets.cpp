/**
 *
 * Assets.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#include "Assets.h"

renderBufferGroup_t renderGroup;

renderBufferGroup_t* kAssets::GetBufferGroup() const {
    return &renderGroup;
}

void kAssets::LoadScene( kScene_t *scene) const {

    /** TODO(Kasper): Get shaders from the scene information. Materials etc. */
    kShaderLoader shaderLoader;
    /** compile and store shaders */
    kShader_t shader = shaderLoader.LoadShaders();
    /** create vertice group */
    CreateVerticeGroup( scene, shader);

    /** load data to the renderer */
    g_Render->LoadScene( scene );

}

void kAssets::CreateVerticeGroup( kScene_t *scene, kShader_t shader) const {
    renderBufferGroup_t group = {};
    group.shader = shader;
    group.ID = 0;
    group.elements = GetAABBVertices( scene->player->aabb);

    renderGroup = group;
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
        PRINTL_STR( "Could not receive filebuffer"); }
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

/** Corners + Element indices */
vertsAndIndices_t* kAssets::GetAABBVertices( const kAABB &aabb) const {

    /** 3 floats per corner, 8 corners */
    u32 nrOfVerts = 3*8;
    /** 3 floats per triangle, 2 triangles per side, 6 sides */
    u32 nrOfIndices = 3*2*6;

    vertsAndIndices_t* result = (vertsAndIndices_t*)g_Memory->Alloc( sizeof(vertsAndIndices_t));
    result->vertices = (f32*)g_Memory->Alloc( nrOfVerts * sizeof(f32) );
    result->indices = (u32*)g_Memory->Alloc( nrOfIndices * sizeof(f32) );

    /** corners */
    vec3 vertice_array[8] = {
        aabb.center - aabb.half,
        aabb.center + Vec3( aabb.half.x, -aabb.half.y, -aabb.half.z),
        aabb.center + Vec3( -aabb.half.x, -aabb.half.y, aabb.half.z),
        aabb.center + Vec3( aabb.half.x, -aabb.half.y, aabb.half.z),
        aabb.center + Vec3( -aabb.half.x, aabb.half.y, -aabb.half.z),
        aabb.center + Vec3( aabb.half.x, aabb.half.y, -aabb.half.z),
        aabb.center + Vec3( -aabb.half.x, aabb.half.y, aabb.half.z),
        aabb.center + aabb.half
    };
    u32 index_array[3*2*6] = {
        0, 2, 1,    3, 1, 2,    /** bottom */
        4, 6, 0,    2, 0, 6,
        7, 2, 6,    3, 2, 7,
        5, 3, 7,    1, 3, 5,
        0, 1, 5,    4, 0, 5,
        6, 4, 5,    7, 6, 5     /** top */
    };


    std::memcpy( result->vertices, vertice_array, nrOfVerts * sizeof(f32));
    std::memcpy( result->indices, index_array, nrOfIndices * sizeof(u32));

    result->vertices_n = nrOfVerts;
    result->indices_n = nrOfIndices;

    return result;
}
