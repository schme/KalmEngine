
#include <windows.h>
#include "Memory.h"

#include "MemoryStack.cpp"

/**
 * kMemory
 */

kMemory::kMemory( u32 byte_size) {
    this->stack = kMemoryStack( byte_size );
}

void *kMemory::alloc( u32 size_bytes ) {
    return this->stack.alloc( size_bytes );
}

void *kMemory::allocAligned( u32 size_bytes, u32 alignment) {
    return this->stack.allocAligned( size_bytes, alignment);
}

void kMemory::free( kMemoryStack::Marker mark ) {
    this->stack.freeToMarker( mark );
}
