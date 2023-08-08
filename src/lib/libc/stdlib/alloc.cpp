#include <stdlib.h>
#include <stdio.h>

limine_memmap_entry *   memblock;
size_t                  memcursor;
size_t                  memlimit;


int
stdlib_init( limine_memmap_response *res )
{
    uint64_t count = res->entry_count;
    memblock  = res->entries[1];
    memcursor = 0;
    memlimit  = res->entries[1]->length;

    return 0;
}


void *
falloc( size_t size )
{
    if (memcursor + size > memlimit)
        memcursor = 0;

    memcursor += size;

    return (void *)((&memblock->base)[memcursor - size]);
}


void *
malloc( size_t size )
{
    return falloc(size);
}


void *
calloc( size_t n, size_t size )
{
    void *ptr = malloc(n*size);

    for (size_t i=0; i<n; i++)
    {
        ((uint8_t *)ptr)[i] = 0;
    }

    return ptr;
}


void
free( void *addr )
{

}

