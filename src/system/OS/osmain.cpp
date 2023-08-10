
#include <stdio.h>
#include <stdlib.h>

#include <system.hpp>
#include <system/terminal.hpp>
#include <system/graphics.hpp>



uint8_t last_data = 0;
int xpos = 200;
int count = 0;
int dir = 1;



int os_init( void )
{

}


int os_mainloop( void )
{
    limine_framebuffer *fb = system::graphics::getfb();

    // auto event = PS2_poll();
    // if (event.type == PS2KeyEventType::KEY_DOWN)
    // {
    //     if (last_data != event.data)
    //     {
    //         last_data = event.data;
    //         printf("%c", (char)(event.data));
    //     }
    // }

    // else if (event.type == PS2KeyEventType::KEY_UP)
    // {
    //     last_data = 0;
    // }

    count += 1;
    if (count % 5000 == 0)
    {
        xpos += dir;
        printf("\0");
        rasterize(fb, {xpos, 500}, {100, 600}, {300, 600});
    
        if (xpos <= 0 || xpos >= 800)
            dir = -dir;
    }

    return 0;
}


