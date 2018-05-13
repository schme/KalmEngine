/*
 *
 * kList
 *
 * Aligned FILO List class.
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 12/05/2018
 */

#ifndef KLIST_H_
#define KLIST_H_


/**
 * Does not have a loop for properly deleting children, so
 * only use with types that do not need recursive resource
 * freeing.
 */
template <typename T>
class kList {
    public:

    kList();
    kList( const kList<T>& orig);
    ~kList<T>();

    kList<T> &  operator=( const kList<T> & orig);
    T& operator[](size_t size);
    const T& operator[](size_t index) const;

    void        push( T item );
    T           pop();
    size_t      size() const;

    T&          back();
    const T&    back() const;
    T&          front();
    const T&    front() const;

    private:
    char *      storage;
    char *      alignedStorage;
    size_t      alignment;
    size_t      paddedTSize;

    /** capacity numbers aren't bytes, but numbers of elements */
    size_t      allocatedCapacity;
    size_t      usedCapacity;

};


/**
 * kList public
 */

template<typename T>
kList<T>::kList() :
storage( nullptr ),
alignedStorage( nullptr ),
alignment( 16 ),
paddedTSize( 0 ),
allocatedCapacity( 0 ),
usedCapacity( 0 )
{
    if( sizeof( T ) % this->alignment != 0 ) {
        this->paddedTSize = this->alignment * (sizeof(T) / this->alignment + 1);
    } else {
        this->paddedTSize = sizeof(T);
    }
}

template<typename T>
kList<T>::kList( const kList<T> &orig) {
    /** TODO(Kasper): implement */
}

template<typename T>
kList<T>::~kList() {
    /** TODO(Kasper): implement */
}

template<typename T>
kList<T> & kList<T>::operator=( const kList<T> & orig) {
    /** TODO(Kasper): implement */
}

template<typename T>
T& kList<T>::operator[](size_t size) {
    /** TODO(Kasper): implement */

}

template<typename T>
const T& kList<T>::operator[](size_t index) const {
    /** TODO(Kasper): implement */
}

template<typename T>
size_t kList<T>::size() const {
    return this->usedCapacity;
}

template<typename T>
void kList<T>::push( T item ) {
    if( this->usedCapacity == this->allocatedCapacity ) {
        /** double the allocated size each time we go over (unless double is less than 2) */
        this->resize( max(this->usedCapacity * 2, 2));
    }
    *(this->top()) = (char*)item;
    this->usedCapacity += 1;
}

template<typename T> inline
T& kList<T>::front() {
    return (*this)[0];
}

template<typename T> inline
const T& kList<T>::front() const {
    return (*this)[0];
}

template<typename T> inline
T& kList<T>::back() {
    return (*this)[this->usedCapacity - 1];
}

template<typename T> inline
const T& kList<T>::back() const {
    return (*this)[this->usedCapacity - 1];
}

/**
 * kList private
 */

template<typename T>
void kList<T>::resize( size_t newSize ) {
    /** TODO(Kasper): implement */
}

#endif /* end of include guard: KLIST_H_ */
