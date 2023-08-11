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



fixed theta;


extern "C"
int os_init( void )
{
    theta = 1;

    return 0;
}

int movy = 0;

extern "C"
int os_loop( void )
{
    mat4 trans = g3d::translate(mat4(1<<16), {250, 250, 0});
    mat4 view(1<<16);


    vec4 v0 = {  0,   -50,  0,  1 };
    vec4 v1 = { -50,   50,  0,  1 };
    vec4 v2 = {  50,   50,  0,  1 };

    count += 1;
    if (count % 5000 == 0)
    {
        theta += 1;

        mat4 rot = g3d::rotate(mat4(1<<16), theta);

        xpos += dir;
        rasterize(trans*rot, v0, v1, v2);
    
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
