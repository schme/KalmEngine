#ifndef KMEMORY_H_
#define KMEMORY_H_

#include "kalm_shared.h"
#include "Systems.h"
#include "MemoryStack.h"


class kMemory : public MemorySystem {
    public:

    kMemory( u32 byte_size);

    /** MemorySystem overrides */
    void *Alloc( u32 size_bytes );
    void *AllocAligned( u32 size_bytes, u32 alignment );
    void Free( Marker mark );

    /** kMemory methods */
    Marker GetMarker() const;
    private:
    kMemoryStack stack;
};


#endif /* end of include guard: KMEMORY_H_ */
