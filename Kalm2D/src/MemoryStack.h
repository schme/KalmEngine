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

        void* Alloc( u32 size_bytes);
        void* AllocAligned( u32 size_bytes, u32 alignment);
        Marker GetMarker() const;
        void FreeToMarker(Marker marker);
        void Clear();

    private:
        void *storage;
        Marker topMark;
        Marker maxMark;
        u32 capacity;

        void *Reserve( const u32 bytes );
        void *VoidFromMarker( Marker mark) const;
        Marker MarkerFromVoid( void* ptr) const;
};


#endif /* end of include guard: MEMORYSTACK_H_ */

