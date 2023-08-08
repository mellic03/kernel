#include <stddef.h>
#include <limine.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <system.hpp>
#include <system/filesystem.hpp>


Sys_stat m_stat = Sys_stat::UNINITIALIZED;

static volatile limine_framebuffer_request  framebuffer_request
{
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

static volatile limine_memmap_request       memmap_request
{
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

static volatile limine_module_request       mod_req
{
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};


limine_framebuffer *
getfb()
{
    return framebuffer_request.response->framebuffers[0];
}


// Halt and catch fire function.
static void hcf(void)
{
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}


Sys_stat
system_init()
{
    // OS initialization -------------------------------------------
    int filesystem_status = filesystem_init(mod_req.response);
    // -------------------------------------------------------------


    // libc initialization -----------------------------------------
    int stdlib_status = stdlib_init(memmap_request.response);
    int stdio_status  = stdio_init(framebuffer_request.response);
    // -------------------------------------------------------------


    printf("\nframebuffers: 1\n");

    printf("\n");

    for (uint64_t i=0; i<memmap_request.response->entry_count; i++)
    {
        limine_memmap_entry *entry = memmap_request.response->entries[i];

        printf("memmap %d\tsize: %d\tbase:%d", i, entry->length, entry->base);

        switch (entry->type)
        {
            case (LIMINE_MEMMAP_USABLE):
                printf("\ttype: usable");
            break;

            case (LIMINE_MEMMAP_RESERVED):
                printf("\ttype: reserved");
            break;

            case (LIMINE_MEMMAP_FRAMEBUFFER):
                printf("\ttype: framebuffer");
            break;
        }

        printf("\n");
    }






    return Sys_stat::GOOD;
}




