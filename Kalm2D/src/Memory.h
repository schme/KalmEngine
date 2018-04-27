#ifndef KMEMORY_H_
#define KMEMORY_H_

#include "kalm_shared.h"
#include "Systems.h"
#include "MemoryStack.h"


class kMemory : public MemorySystem {
    public:
    kMemory( u32 byte_size);
    void *alloc( u32 size_bytes );
    void *allocAligned( u32 size_bytes, u32 alignment );
    void free( Marker mark );

    private:
    kMemoryStack stack;
};

//extern "C" MemorySystem * GetMemorySystem();

#endif /* end of include guard: KMEMORY_H_ */
