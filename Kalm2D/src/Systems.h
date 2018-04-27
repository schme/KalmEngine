#ifndef SYSTEMS_H_
#define SYSTEMS_H_


#include "kalm_shared.h"


class MemorySystem {
    public:
    typedef u32 Marker;
    virtual void *alloc( u32 size_bytes ) =0;
    virtual void *allocAligned( u32 size_bytes, u32 alignment ) =0;
    virtual void free( Marker mark ) =0;
};

#endif /* end of include guard: SYSTEMS_H_ */
