#pragma once

#include <stdint.h>
#include <stddef.h>
#include <limine.hpp>

#ifdef __cplusplus
extern "C" {
#endif



void *      memcpy  ( void *dest, const void *src, size_t n );
void *      memset  ( void *s, int c, size_t n );
void *      memmove ( void *dest, const void *src, size_t n );
int         memcmp  ( const void *s1, const void *s2, size_t n );



/** Fast malloc
 *  Does not guarantee data will not be overwritten.
 *  Limited size! Only use for small allocations!
*/
void *      fmalloc ( size_t size );
void *      malloc  ( size_t size );
void *      calloc  ( size_t n, size_t size );
void        free    ( void *addr  );



#ifdef __cplusplus
}
#endif
