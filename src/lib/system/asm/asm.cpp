#include <system/asm.hpp>


void
system::hcf( void )
{
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

