#include "libc.h"



void libc_init( limine_memmap_response *mres,
                limine_framebuffer_response *fres )
{
    alloc_init(mres);
    stdio_init(fres);
}

