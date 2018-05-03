/**
 *
 * Kasper Common Library
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 25/04/2018
 */

#ifndef KCL_HPP_
#define KCL_HPP_

#include <cstdio>
#include "Types.h"

#include <stdexcept>

#define Kilobytes( value ) (1024LL * (value))
#define Megabytes( value ) (1024LL * Kilobytes( (value)))
#define Gigabytes( value ) (1024LL * Megabytes( (value)))


#define PRINTL_STR( string)\
    printf("%s(%d): %s\n", __FILE__, __LINE__, (string))

#define PRINT_STR( string)\
    printf("%s(%d): %s", __FILE__, __LINE__, (string))

#if K_ASSERT

//TODO(Kasper): Doesn't actually work, do something with it

#define debugBreak() //asm { int 3 }

#define ASSERT(expr)\
    if( (expr) ){}\
    else {\
        ReportAssertionFailure(#expr,\
                __FILE__, __LINE__);\
        throw kException( #expr);\
    }

void ReportAssertionFailure( const char *expression, const char *file, const i32 line);

#else
#define ASSERT(expr)    /* Empty definition */
#endif


class kException: public std::runtime_error {
public:
    kException() : std::runtime_error("General kException") {}
    kException(const std::string& message) : std::runtime_error(message) {}
private:
};

u32 safeCastU32ToU16( u64 value);
u16 safeCastU32ToU16( u32 value);


/**
 * Implementations
 */

#ifdef KCL_IMPLEMENTATION


u32 safeCastU64ToU32( u64 value ) {
    if(( 0xFFFFFFFF00000000 & value ) == 0) {
        return (u32)value;
    } else {
        throw( kException( "safeCastU64ToU32 was not safe"));
    }
}

u16 safeCastU32ToU16( u32 value ) {
    if(( 0xFFFF0000 & value ) == 0) {
        return (u16)value;
    } else {
        throw( kException( "safeCastU32ToU16 was not safe"));
    }
}


#if K_ASSERT
void ReportAssertionFailure( const char *expression, const char *file, const i32 line) {
    printf( "ASSERT: %s FAILED -- %s: %d\n", expression, file, line);
}

#endif
#endif
#endif /* end of include guard: KCL_HPP_ */
