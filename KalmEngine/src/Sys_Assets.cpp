/**
 *
 * Assets.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 28/04/2018
 */


#include "Sys_Assets.h"

#include "Sys_ImageLoader.cpp"
#include "Sys_MeshLoader.cpp"

kImage_t* kAssets::LoadImage( const char *filename) const {
    return this->imageLoader.LoadImage( filename );
}

kMesh_t* kAssets::LoadMesh( const char *filename) const {
    return this->meshLoader.LoadMesh( filename );
}
