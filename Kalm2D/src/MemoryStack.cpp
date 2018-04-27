/**
 *
 * kMemoryStack.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include <windows.h>
#include "WinBase.h"
#include "MemoryStack.h"

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

        this->storage = this->reserve(size);

        /* check we got the memory */
        if( this->storage) {
            this->capacity = size;
            this->topMark = markerFromVoid(this->storage);
            this->maxMark = markerFromVoid(this->storage) + this->capacity;
        } else {
            PRINT_STR( "kMemoryStack: Constructor could not get storage");
        }
}


kMemoryStack::kMemoryStack( const kMemoryStack &orig) {
        this->clear();
        if( orig.capacity > 0) {
            this->capacity = orig.capacity;
            this->storage = this->reserve( orig.capacity);
            if( this->storage) {
                /* copy the storage over */
                std::memcpy( this->storage, orig.storage, orig.capacity);
                this->maxMark = markerFromVoid(this->storage) + this->capacity;
                this->topMark = markerFromVoid(this->storage);

            } else {
                PRINT_STR( "kMemoryStack: Constructor could not get storage");
            }
        }
}


kMemoryStack::~kMemoryStack() {
    this->clear();
}


kMemoryStack& kMemoryStack::operator=( const kMemoryStack &orig) {
    this->clear();
    this->capacity = orig.capacity;
    this->storage = this->reserve( orig.capacity);
    if( this->storage) {
        /* copy the storage over */
        std::memcpy( this->storage, orig.storage, orig.capacity);
        this->maxMark = markerFromVoid(this->storage) + this->capacity;
        this->topMark = markerFromVoid(this->storage);

    } else {
        PRINT_STR( "kMemoryStack: operator= overload could not get storage");
    }
    return *this;
}


void* kMemoryStack::reserve( const u32 bytes) {
    if( bytes == 0) {
        return nullptr;
    }
    /* TODO(Kasper):  Commit the memory later */
    void *newStorage = VirtualAlloc( nullptr, bytes, MEM_COMMIT, PAGE_READWRITE);
    return newStorage;
}

void kMemoryStack::freeToMarker( Marker marker) {
    this->topMark = marker;
}

void kMemoryStack::clear() {
    this->topMark = markerFromVoid(this->storage);
    this->maxMark = this->topMark;
    this->capacity = 0;

    VirtualFree( this->storage, 0, MEM_RELEASE );
    this->storage = nullptr;
}

/* Allocate size_bytes area with no concern for alignment */
void *kMemoryStack::alloc( u32 size_bytes ) {
    //TODO(Kasper): Check if needs to be >=
    if( markerFromVoid(this->storage) + capacity > (this->topMark + size_bytes)) {
        PRINT_STR( "Tried to allocate more memory than kMemoryStack has available");
        return nullptr;
    }

    void *return_ptr = voidFromMarker(this->topMark);
    this->topMark += size_bytes;
    this->capacity += size_bytes;

    return return_ptr;
}


/* Allocate size_bytes area with aligned to byte_alignment */
void *kMemoryStack::allocAligned( u32 size_bytes, u32 byte_alignment) {
    //TODO(Kasper): ASSERT((alignment & (alignment - 1)) = 0); // pwr of 2
    u32 expandSize_bytes = size_bytes + byte_alignment;
    u64 rawAddress = markerFromVoid( alloc( expandSize_bytes));
    u32 mask = (byte_alignment - 1);
    u64 alignOffsetAmount = (rawAddress & mask);
    ptrdiff_t adjustment = byte_alignment - alignOffsetAmount;

    uintptr_t alignedAddress = rawAddress + adjustment;
    return (void*)(alignedAddress);
}

void *kMemoryStack::voidFromMarker( Marker mark) const {
    return reinterpret_cast<void*>(mark);
}

kMemoryStack::Marker kMemoryStack::markerFromVoid( void *ptr) const {
    return reinterpret_cast<u64>(ptr);
}

