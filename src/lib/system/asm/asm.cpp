#include <system/asm.hpp>
#include <time.h>

void
system::hcf( void )
{
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}


uint64_t
system::tickrate( void )
{
    return CLOCKS_PER_SEC;
}


