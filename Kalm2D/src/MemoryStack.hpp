#ifndef MEMORYSTACK_HPP_U8CECPJO
#define MEMORYSTACK_HPP_U8CECPJO



#include "Types.h"


template <typename T>
__declspec(align(16))
class kMemoryStack {
    public:

        static const size_t alignment = 16;

        kMemoryStack();
        kMemoryStack( const kMemoryStack<T> &orig);
        kMemoryStack<T>& operator=( const kMemoryStack<T> &orig);

        ~kMemoryStack();

        T* pop();
        void push(T element);

    private:
        char *storage;
        char *alignedPtr;
        char * top;
        char * topElement;
        /* padded for alignment if necessary */
        size_t elemBytes;
        size_t filledCapacity;
        size_t totalCapacity;

        void resize( size_t newSize);
};

template <typename T>
kMemoryStack<T>::kMemoryStack() :
    storage(nullptr),
    alignedPtr(nullptr),
    top(nullptr),
    topElement(nullptr),
    filledCapacity(0),
    totalCapacity(0) {


        /* Make sure we store T aligned */
        if( sizeof(T) % this->alignment != 0) {
            this->elemBytes = this->alignment * ( sizeof(T) / this->alignment + 1 );
        } else {
            this->elemBytes = sizeof(T);
        }

}


template <typename T>
kMemoryStack<T>::kMemoryStack( const kMemoryStack<T> &orig) {
    while( filledCapacity > 0) {
        this->pop();
    }
    free( this->storage);
    T *iter_ptr = orig.storage;
    this->resize( orig.totalCapacity);
    while( (iter_ptr += this->elemBytes) <= orig.top ) {
        this->push( (*iter_ptr) );
    }
}


template <typename T>
T* kMemoryStack<T>::pop() {
    if( this->top == this->storage ) {
        return nullptr;
    }
    this->filledCapacity--;
    this->top -= this->elemBytes;
    this->topElement -= this->elemBytes;
    return this->top;
}


template <typename T>
void kMemoryStack<T>::push(T element) {

    /* need more space */
    if( filledCapacity >= totalCapacity ) {
        this->resize( max( totalCapacity * 2, totalCapacity + 4) );
    }
    *(this->top) = element;
    (this->top)++;
    if( filledCapacity != 0) {
        (this->topElement)++;
    }
    this->filledCapacity++;
}


template <typename T>
void kMemoryStack<T>::resize( size_t newSize) {
    if( this->totalCapacity >= newSize) {
        return;
    }
    char *newStorage = malloc( newSize);


    while( this->filledCapacity-- > 0) {
        free(this->topElement);
    }
    this->storage = newStorage;
    this->top = newStorage;
    this->topElement = nullptr;
}


#endif /* end of include guard: MEMORYSTACK_HPP_U8CECPJO */

