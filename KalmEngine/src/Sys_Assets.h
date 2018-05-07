/**
 *
 * AssetSystem
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */

#ifndef ASSETS_H_
#define ASSETS_H_


#include "Sys_Shared.h"
#include "Sys_ImageLoader.h"
#include "Object.h"
#include "KalmTypes.h"
#include "Systems.h"
#include "Scene.h"
#include "Shader.h"

class kAssets : public AssetSystem {
    public:
    ImageLoader imageLoader;
    /** AssetSystem overrides */
    kImage_t *LoadImage( const char *filename) const;
    private:
};



#endif /* end of include guard: ASSETS_H_ */

