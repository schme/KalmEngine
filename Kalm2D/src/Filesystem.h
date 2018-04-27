/**
 *
 * Filesystem
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018 
 */

#include "Types.h"

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_


class kFilesystem {
    public:
        i32 LoadFile( const char *filename, void *buffer) const;
        u64 GetFileSize( const char *filename ) const;
    private:
};

#endif /* end of include guard: FILESYSTEM_H_ */
