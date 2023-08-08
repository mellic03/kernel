#include <limine.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

static volatile struct limine_module_request mod_req = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};


// Halt and catch fire function.
static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}


uint32_t gethex( uint32_t r, uint32_t g, uint32_t b )
{
    return (r << 16) + (g << 8) + b;
}


extern "C" void _start(void)
{
    // Ensure we have the framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the memory map.
    alloc_init(memmap_request.response);

    // Fetch the first framebuffer.
    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
    struct Terminal terminal = terminal_new(fb);


    // Fetch multiboot modules
    struct limine_module_response *module_res = mod_req.response;
    if (module_res == NULL)
    {
        terminal_printf(terminal, "\n\nruh roh, no module response\n\n");
    }


    limine_file *fh = module_res->modules[0]; 
    char *baseptr = (char *)(fh->address);

    for (uint64_t i=0; i<fh->size; i++)
    {
        terminal_printf(terminal, "%c", *(baseptr + i));
    }
    // terminal_printf(terminal, "modules: %d\n\n", module_res->module_count);
    // for (uint64_t i=0; i<module_res->module_count; i++)
    // {
    //     terminal_printf(terminal, "module %d, address %d\n", i, module_res->modules[i]->address);
    // }
    // terminal_printf(terminal, "\n");



    terminal_printf(terminal, "framebuffers detected: %d\n", framebuffer_request.response->framebuffer_count);


    for (uint64_t i=0; i<memmap_request.response->entry_count; i++)
    {
        limine_memmap_entry *entry = memmap_request.response->entries[i];

        terminal_printf(terminal, "memmap %d\tsize: %d\tbase:%d", i, entry->length, entry->base);

        switch (entry->type)
        {
            case (LIMINE_MEMMAP_USABLE):
                terminal_putstr(terminal, "\ttype: usable");
            break;

            case (LIMINE_MEMMAP_RESERVED):
                terminal_putstr(terminal, "\ttype: reserved");
            break;
        }

        terminal_putstr(terminal, "\n");
    }

    uint8_t last_data = 0;

    while (1)
    {
        auto event = PS2_poll();
        if (event.type == PS2KeyEventType::KEY_DOWN)
        {
            if (last_data != event.data)
            {
                last_data = event.data;
                terminal_putchar(terminal, (char)(event.data));
            }
        }

        else if (event.type == PS2KeyEventType::KEY_UP)
        {
            last_data = 0;
        }
    }


    // We're done, just hang...
    hcf();
}

