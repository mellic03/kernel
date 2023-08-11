#include <system.hpp>
#include <system/asm.hpp>
#include <system/graphics.hpp>
#include <system/terminal.hpp>

#include "../OS/os_entry.hpp"


extern "C"
void kernel_entry( void )
{
    int sys_status = kernel_init();
    int os_status  = os_init();

    int framecount = 0;

    while (1)
    {
        framecount += 1;

        if (framecount % 5000 == 0)
        {
            system::graphics::swap_buffers();
            system::terminal::render();
            framecount = 0;
        }

        os_status = os_loop();

    }

}

