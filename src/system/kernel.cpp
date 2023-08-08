#include <limine.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <system/terminal.hpp>
#include <system.hpp>

#include <system/ps2.h>
#include <system/graphics.hpp>



extern "C"
void main( void )
{
    Sys_stat status = system_init();
    limine_framebuffer *fb = getfb();

    uint8_t last_data = 0;

    while (1)
    {
        auto event = PS2_poll();
        if (event.type == PS2KeyEventType::KEY_DOWN)
        {
            if (last_data != event.data)
            {
                last_data = event.data;
                printf("%c", (char)(event.data));
                rasterize(fb, {200, 500}, {100, 600}, {300, 600});
            }
        }

        else if (event.type == PS2KeyEventType::KEY_UP)
        {
            last_data = 0;
        }
    }


    // We're done, just hang...
    // hcf();
}

