
#include <windows.h>
#include "Memory.h"

#include "MemoryStack.cpp"

/**
 * kMemory
 */

kMemory::kMemory( u32 byte_size) {
    this->stack = kMemoryStack( byte_size );
}


/** MemorySystem overrides */


void *kMemory::Alloc( u32 size_bytes ) {
    return this->stack.Alloc( size_bytes );
}

void *kMemory::AllocAligned( u32 size_bytes, u32 alignment) {
    return this->stack.AllocAligned( size_bytes, alignment);
}

void kMemory::Free( Marker mark ) {
    this->stack.FreeToMarker( mark );
}


/** kMemory methods */


kMemory::Marker kMemory::GetMarker() const {
    return this->stack.GetMarker();
}
