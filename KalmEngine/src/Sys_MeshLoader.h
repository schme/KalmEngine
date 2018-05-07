/**
 *
 * Sys_MeshLoader.h
 *
 * Supports PLY files through tinyply library
 * uses STL quite freely
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 07/05/2018
 */

#ifndef SYS_MESHLOADER_H_41ETIUKG
#define SYS_MESHLOADER_H_41ETIUKG

#include "KalmTypes.h"

class MeshLoader {
    public:
    kMesh_t *       LoadMesh( const char *filename) const;
    private:
    kMesh_t *          LoadPLY( const char *filename ) const;
};


#endif /* end of include guard: SYS_MESHLOADER_H_41ETIUKG */
