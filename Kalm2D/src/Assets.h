/**
 *
 * AssetSystem
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#ifndef ASSETS_H_
#define ASSETS_H_


#include "kalm_shared.h"
#include "Systems.h"
#include "SystemsLocal.h"
#include "Scene.h"
#include "Shader.h"

class kAssets : public AssetSystem {
    public:
    /** AssetSystem overrides */
    kImage_t *GetImage( const char *filename) const;

    /** kAssets methods */
    void LoadScene( kScene_t *scene) const;
    private:
    kShader_t *GetShader( const char *filename) const;
    kImage_t *LoadBMPFile( const char *filename, const void *filebuffer ) const;
    void CreateVerticeGroups( kScene_t *scene) const;
};


struct renderBufferGroup_t {
    f32 *vertices;
    u32 ID;
    u32 numberOfVertices;
    u32 shaderID;
};


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


#endif /* end of include guard: ASSETS_H_ */

