#ifndef KMEMORY_H_
#define KMEMORY_H_

#include "kalm_shared.h"
#include "MemoryStack.h"

class kMemory {
    public:
    kMemory( u32 byte_size);
    void *alloc( u32 size_bytes );
    void *allocAligned( u32 size_bytes, u32 alignment );
    void free( kMemoryStack::Marker mark );

    private:
    kMemoryStack stack;
};

#endif /* end of include guard: KMEMORY_H_ */
