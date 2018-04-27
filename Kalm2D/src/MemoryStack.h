#ifndef MEMORYSTACK_H_
#define MEMORYSTACK_H_

#include "kalm_shared.h"

/*
 * Uses VirtualMemory, so allocating page sized things is usually easier
 * Uses 64bit memory addresses
 */
class kMemoryStack {
    public:
        typedef u64 Marker;

        kMemoryStack();
        kMemoryStack( const u32 size);
        kMemoryStack( const kMemoryStack &orig);
        kMemoryStack& operator=( const kMemoryStack &orig);

        ~kMemoryStack();

        void* alloc( u32 size_bytes);
        void* allocAligned( u32 size_bytes, u32 alignment);
        Marker getMarker();
        void freeToMarker(Marker marker);
        void clear();

    private:
        void *storage;
        Marker topMark;
        Marker maxMark;
        u32 capacity;

        void *reserve( const u32 bytes );
        void *voidFromMarker( Marker mark) const;
        Marker markerFromVoid( void* ptr) const;
};


#endif /* end of include guard: MEMORYSTACK_H_ */

