#include <stdlib.h>
#include <stdio.h>

#include <system/filesystem.hpp>


void *
falloc( size_t size )
{
    return system::fs::get_memory(size);
}


void *
malloc( size_t size )
{
    return falloc(size);
}


void *
calloc( size_t n, size_t typesize )
{
    uint8_t *ptr = (uint8_t *)malloc(n*typesize);

    for (size_t i=0; i<n; i++)
    {
        ptr[i] = 0;
    }

    return (void *)ptr;
}


void
free( void *addr )
{

}

