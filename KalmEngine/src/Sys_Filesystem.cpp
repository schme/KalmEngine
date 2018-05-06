/**
 *
 * Filesystem
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018 
 */

#include <windows.h>
#include "Sys_Filesystem.h"

/** TODO(Kasper): Bad dev versions
 *
 * Synchronous file handling. Read the whole file and continue.
 * Can't handle files past 4Gigs (DWORD/U32 limit)
 */


/** Handle doesn't allow reads, writes or anything from others */
i32 kFilesystem::ReadWholeFile( const char *filename, const u32 buffer_size, void *buffer) const {

    OVERLAPPED overlapped;
    DWORD bytes_read = 0;
    HANDLE file = CreateFile( filename, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, NULL);
    if( file == INVALID_HANDLE_VALUE ) {
        PRINT_STR( "FAIL Opening file: ");
        this->ReportLastError();
        return false;
    }

    b32 success = 0;
    success = ReadFile( file, buffer, buffer_size, &bytes_read, &overlapped);

    if( !success) {
        PRINT_STR( "FAIL Reading file: ");
        this->ReportLastError();
        return 0;
    }
    CloseHandle( file );
    return success;
}


i32 kFilesystem::WriteWholeFile( const char *filename, const u32 buffer_size, const void *buffer) const {
    OVERLAPPED overlapped;
    DWORD bytesWritten = 0;
    HANDLE file = CreateFile( filename, GENERIC_WRITE, 0, 0, CREATE_NEW, 0, NULL);
    if( file == INVALID_HANDLE_VALUE) {
        PRINT_STR( "FAIL Opening file: ");
        this->ReportLastError();
        return false;
    }

    b32 success = 0;
    success = WriteFile( file, buffer, buffer_size, &bytesWritten, &overlapped);

    if( !success ) {
        PRINT_STR( "FAIL Reading file: ");
        this->ReportLastError();
    }
    CloseHandle( file );
    return bytesWritten;
}


b32 kFilesystem::GetWholeFileSize( const char *filename, u64 *file_size ) const {
    b32 result;
    LARGE_INTEGER fileSize;
    HANDLE file = CreateFile( filename, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, NULL);
    result = GetFileSizeEx( file, &fileSize );
    CloseHandle( file );
    *file_size = fileSize.QuadPart;
    return result;
}


void kFilesystem::ReportLastError() const {
        void * lpMsgBuf;

        DWORD err = GetLastError();
        FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                err,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0, NULL );
        PRINT_STR( (char*)lpMsgBuf);
}
