#include "os_entry.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <system.hpp>
#include <system/asm.hpp>
#include <system/drivers/ps2.hpp>
#include <system/terminal.hpp>
#include <system/graphics.hpp>



int xpos = 200;
int count = 0;
int dir = 1;

bool released = true;
char last_pressed;



extern "C"
int os_init( void )
{
    uint64_t tickrate = system::tickrate();
    printf("tickrate: %d\n", tickrate);

    vec4 vec = { 1, 1, 1, 1 };
    mat4 mat(1<<16);

    printf("%d %d %d %d\n", vec.x, vec.y, vec.z, vec.w);

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            printf("%d ", mat.data[4*i+j]);
        }
        printf("\n");
    }
    printf("\n");


    return 0;
}


extern "C"
int os_loop( void )
{
    count += 1;
    if (count % 5000 == 0)
    {
        xpos += dir;
        rasterize({xpos, 500}, {100, 600}, {300, 600});
    
        if (xpos <= 80 || xpos >= 320)
            dir = -dir;
    }

    char key;
    if (system::ps2::keydown(key))
    {
        if (last_pressed != key)
        {
            last_pressed = key;
            printf("%c", (char)(key));
        }
    }

    else if (system::ps2::keyup(key))
    {
        last_pressed = 0;
    }


    return 0;
}
