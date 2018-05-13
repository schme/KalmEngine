/**
 *
 * kMemoryStack.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include <windows.h>
#include "WinBase.h"
#include "Sys_MemoryStack.h"
#include "kcl.hpp"


//TODO(Kasper): Change mark to be relative from the storage (as it stands it's kinda useless);


kMemoryStack::kMemoryStack() :
    storage(nullptr),
    topMark(0U),
    maxMark(0U),
    capacity(0U)
{
    /** empty body */
}

kMemoryStack::kMemoryStack( u32 size) :
    storage(nullptr),
    topMark(0U),
    maxMark(0U) {

        if( size == 0) { return; }

        this->storage = this->Reserve(size);

        /* check we got the memory */
        if( this->storage) {
            this->capacity = size;
            this->topMark = MarkerFromVoid(this->storage);
            this->maxMark = MarkerFromVoid(this->storage) + this->capacity;
        } else {
            PRINTL_STR( "kMemoryStack: Constructor could not get storage");
        }
}


kMemoryStack::kMemoryStack( const kMemoryStack &orig) {
        this->Clear();
        if( orig.capacity > 0) {
            this->capacity = orig.capacity;
            this->storage = this->Reserve( orig.capacity);
            if( this->storage) {
                /* copy the storage over */
                std::memcpy( this->storage, orig.storage, orig.capacity);
                this->maxMark = MarkerFromVoid(this->storage) + this->capacity;
                this->topMark = MarkerFromVoid(this->storage);

            } else {
                PRINTL_STR( "kMemoryStack: Constructor could not get storage");
            }
        }
}


kMemoryStack::~kMemoryStack() {
    this->Clear();
}


kMemoryStack& kMemoryStack::operator=( const kMemoryStack &orig) {
    this->Clear();
    this->capacity = orig.capacity;
    this->storage = this->Reserve( orig.capacity);
    if( this->storage) {
        /* copy the storage over */
        std::memcpy( this->storage, orig.storage, orig.capacity);
        this->maxMark = MarkerFromVoid(this->storage) + this->capacity;
        this->topMark = MarkerFromVoid(this->storage);

    } else {
        PRINTL_STR( "kMemoryStack: operator= overload could not get storage");
    }
    return *this;
}


kMemoryStack::Marker kMemoryStack::GetMarker() const {
    return this->topMark;
}

void* kMemoryStack::Reserve( const u32 bytes) {
    if( bytes == 0) {
        return nullptr;
    }
    /* TODO(Kasper):  Commit the memory later */
    void *newStorage = VirtualAlloc( nullptr, bytes, MEM_COMMIT, PAGE_READWRITE);
    return newStorage;
}

void kMemoryStack::FreeToMarker( Marker marker) {
    this->topMark = marker;
}

void kMemoryStack::Clear() {
    this->topMark = MarkerFromVoid(this->storage);
    this->maxMark = this->topMark;
    this->capacity = 0;

    VirtualFree( this->storage, 0, MEM_RELEASE );
    this->storage = nullptr;
}

/* Allocate size_bytes area with no concern for alignment */
void *kMemoryStack::Alloc( u32 size_bytes ) {
    //TODO(Kasper): Check if needs to be >=
    if( this->maxMark < (this->topMark + size_bytes)) {
        ASSERT(!"Tried to allocate more memory than kMemoryStack has available");
        PRINTL_STR( "Tried to allocate more memory than kMemoryStack has available");
        return nullptr;
    }

    void *return_ptr = VoidFromMarker(this->topMark);
    this->topMark += size_bytes;
    this->capacity += size_bytes;

    return return_ptr;
}


/* Allocate size_bytes area with aligned to byte_alignment */
void *kMemoryStack::AllocAligned( u32 size_bytes, u32 byte_alignment) {
    //ASSERT((alignment & (alignment - 1)) == 0); // pwr of 2

    u32 expandSize_bytes = size_bytes + byte_alignment;
    u64 rawAddress = MarkerFromVoid( Alloc( expandSize_bytes));
    u32 mask = (byte_alignment - 1);
    u64 alignOffsetAmount = (rawAddress & mask);
    ptrdiff_t adjustment = byte_alignment - alignOffsetAmount;

    uintptr_t alignedAddress = rawAddress + adjustment;
    return (void*)(alignedAddress);
}

void *kMemoryStack::VoidFromMarker( Marker mark) const {
    return reinterpret_cast<void*>(mark);
}

kMemoryStack::Marker kMemoryStack::MarkerFromVoid( void *ptr) const {
    return reinterpret_cast<u64>(ptr);
}

