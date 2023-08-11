#include <limine.hpp>

#include <system.hpp>
#include <system/filesystem.hpp>
#include <system/terminal.hpp>
#include <system/graphics.hpp>

#include <stdio.h>


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



int
kernel_init()
{
    // Kernel initialization -------------------------------------------
    int filesystem_status = system::fs::init(memmap_request.response);
    int graphics_status   = system::graphics::init(framebuffer_request.response);
    int terminal_status   = system::terminal::init(mod_req.response->modules[0]);
    // -------------------------------------------------------------

    load_fixed_trigtables((int32_t *)mod_req.response->modules[1]->address);


    printf("\n");
    for (size_t i=0; i<mod_req.response->module_count; i++)
    {
        auto mod = mod_req.response->modules[i];
        printf("module %d\tsize %d\tbase: %d\n", i, mod->size, (uint64_t)(mod->address));
    }
    printf("\n");


    for (uint64_t i=0; i<memmap_request.response->entry_count; i++)
    {
        limine_memmap_entry *entry = memmap_request.response->entries[i];

        printf("memmap %d\tsize: %d\tbase: %d", i, entry->length, entry->base);

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


    return 0;
}




