#pragma once

#include <stdint.h>
#include <stddef.h>
#include <limine.hpp>


void        alloc_init( limine_memmap_response *res );

void *      malloc ( size_t size );
void *      calloc ( size_t n, size_t size );

/** Fast malloc
 *  Does not guarantee data will not be overwritten.
*/
void *      falloc ( size_t size );

void        free   ( void *addr  );

