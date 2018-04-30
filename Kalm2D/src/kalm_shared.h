#ifndef KALM_SHARED_H_
#define KALM_SHARED_H_

#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "stdafx.h"
#include "Types.h"

#define KCL_IMPLEMENTATION
#include "kcl.hpp"
#undef KCL_IMPELMENTATION

struct kImage_t {
    u16 width;
    u16 height;
    u32 reserved;
    u64 assetMark;
    u64 bufferSize;
    const char *filename;
    void *imageBuffer;
};

#endif /* end of include guard: KALM_SHARED_H_ */
