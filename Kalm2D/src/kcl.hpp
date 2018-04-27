/**
 *
 * Kasper Common Library
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 25/04/2018
 */

#include "Types.h"


#ifndef KCL_HPP_
#define KCL_HPP_

#include <stdexcept>


#define PRINTL_STR( string)\
    printf("%s\n", (string))

#define PRINT_STR( string)\
    printf("%s", (string))

#if K_ASSERT

//TODO(Kasper): Doesn't actually work, do something with it

#define debugBreak() asm { int 3 }

#define ASSERT(expr)\
    if( expr ) { }\
    else {\
        ReportAssertionFailure(#expr,\
                __FILE__, __LINE__);\
        debugBreak();\
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

#if KCL_IMPLEMENTATION

#if K_ASSERT
void ReportAssertionFailure( const char *expression, const char *file, const i32 line) {
    printf( "%s FAILED -- %s: %s\n", expression, file, line);
}

#endif
#endif
#endif /* end of include guard: KCL_HPP_ */
