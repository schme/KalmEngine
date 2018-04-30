/**
 *
 * Filesystem
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include "Types.h"
#include "Systems.h"

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_


class kFilesystem : public FileSystem {
    public:
        /* FileSystem overrides */
        b32 ReadWholeFile( const char *filename, const u32 buffer_size, void *buffer) const;
        b32 WriteWholeFile( const char *filename, const u32 buffer_size, const void *buffer) const;
        b32 GetWholeFileSize( const char *filename, u64 *file_size ) const;

        /* kFilesystem methods */
        b32 LoadBMPFile( const void *fileBuffer, const u32 buffer_size, void *bmp_buffer) const;

    private:
        void ReportLastError() const;
};

#endif /* end of include guard: FILESYSTEM_H_ */
