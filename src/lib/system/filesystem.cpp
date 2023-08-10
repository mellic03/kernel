#include <system/filesystem.hpp>
#include <stddef.h>


limine_memmap_entry *sysfs_fast_memory;
limine_memmap_entry *sysfs_main_memory;



int
system::fs::init( limine_memmap_response *res )
{
    sysfs_fast_memory = res->entries[1];
    sysfs_main_memory = res->entries[4];

    return 0;
}


void *
system::fs::get_fast_memory( size_t num_bytes )
{
    static uint64_t cursor = 0;

    uint64_t length  = sysfs_fast_memory->length;
    uint8_t *baseptr = (uint8_t *)(sysfs_fast_memory->base);

    if (cursor + num_bytes > length)
        cursor = 0;

    cursor += num_bytes;

    return baseptr + (cursor - num_bytes);
}


void *
system::fs::get_memory( size_t num_bytes )
{
    static uint64_t cursor = 0;

    uint64_t length  = sysfs_main_memory->length;
    uint8_t *baseptr = (uint8_t *)(sysfs_main_memory->base);

    if (cursor + num_bytes > length)
        cursor = 0;

    cursor += num_bytes;

    /*
        store cursor and size in some lookup data structure.
    */

    return baseptr + (cursor - num_bytes);
}


void
system::fs::free_memory( void *addr )
{
    // size_t length = lookupDS.get(addr);
}



