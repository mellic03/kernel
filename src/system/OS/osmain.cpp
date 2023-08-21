#include "os_entry.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <system.hpp>
#include <system/asm.hpp>
#include <system/drivers/ps2.hpp>
#include <system/terminal.hpp>
#include <system/graphics.hpp>



bool released = true;
char last_pressed;


g3d::vertex *vertices;
fixed yaw(0);


extern "C"
int os_init( void )
{
    vertices = (g3d::vertex *)malloc(36*sizeof(g3d::vertex));

    vertices[0]  = { -2, -2, -2, 1,     0,  0, -1,  0 };
    vertices[1]  = {  2, -2, -2, 1,     0,  0, -1,  0 };
    vertices[2]  = {  2,  2, -2, 1,     0,  0, -1,  0 };

    vertices[3]  = {  2,  2, -2, 1,     0,  0, -1,  0 };
    vertices[4]  = { -2,  2, -2, 1,     0,  0, -1,  0 };
    vertices[5]  = { -2, -2, -2, 1,     0,  0, -1,  0 };

    vertices[6]  = { -2, -2,  2, 1,     0,  0,  1,  0 };
    vertices[7]  = {  2, -2,  2, 1,     0,  0,  1,  0 };
    vertices[8]  = {  2,  2,  2, 1,     0,  0,  1,  0 };

    vertices[9]  = {  2,  2,  2, 1,     0,  0,  1,  0 };
    vertices[10] = { -2,  2,  2, 1,     0,  0,  1,  0 };
    vertices[11] = { -2, -2,  2, 1,     0,  0,  1,  0 };

    vertices[12] = { -2,  2,  2, 1,    -1,  0,  0,  0 };
    vertices[13] = { -2,  2, -2, 1,    -1,  0,  0,  0 };
    vertices[14] = { -2, -2, -2, 1,    -1,  0,  0,  0 };

    vertices[15] = { -2, -2, -2, 1,    -1,  0,  0,  0 };
    vertices[16] = { -2, -2,  2, 1,    -1,  0,  0,  0 };
    vertices[17] = { -2,  2,  2, 1,    -1,  0,  0,  0 };

    vertices[18] = {  2,  2,  2, 1,     1,  0,  0,  0 };
    vertices[19] = {  2,  2, -2, 1,     1,  0,  0,  0 };
    vertices[20] = {  2, -2, -2, 1,     1,  0,  0,  0 };

    vertices[21] = {  2, -2, -2, 1,     1,  0,  0,  0 };
    vertices[22] = {  2, -2,  2, 1,     1,  0,  0,  0 };
    vertices[23] = {  2,  2,  2, 1,     1,  0,  0,  0 };

    vertices[24] = { -2, -2, -2, 1,     0, -1,  0,  0 };
    vertices[25] = {  2, -2, -2, 1,     0, -1,  0,  0 };
    vertices[26] = {  2, -2,  2, 1,     0, -1,  0,  0 };

    vertices[27] = {  2, -2,  2, 1,     0, -1,  0,  0 };
    vertices[28] = { -2, -2,  2, 1,     0, -1,  0,  0 };
    vertices[29] = { -2, -2, -2, 1,     0, -1,  0,  0 };

    vertices[30] = { -2,  2, -2, 1,     0,  1,  0,  0 };
    vertices[31] = {  2,  2, -2, 1,     0,  1,  0,  0 };
    vertices[32] = {  2,  2,  2, 1,     0,  1,  0,  0 };

    vertices[33] = {  2,  2,  2, 1,     0,  1,  0,  0 };
    vertices[34] = { -2,  2,  2, 1,     0,  1,  0,  0 };
    vertices[35] = { -2,  2, -2, 1,     0,  1,  0,  0 };


    fixed f = 5;
    fixed s = fixed_sqrt(f);
    printf("root f: ");
    system::terminal::putfixed(s.data);
    printf("\n");


    return 0;
}


fixed theta(0);
fixed theta2(0);

extern "C"
int os_loop( void )
{
    mat4 proj  = g3d::perspective(70, fixed(1280)/fixed(800), 1, 100);
    mat4 trans = g3d::translate(mat4(1), {2, 0, 20});
    mat4 rot   = g3d::rotateY(mat4(1), theta);
    mat4 rot2   = g3d::rotateZ(mat4(1), theta2);
    mat4 trans2 = g3d::translate(mat4(1), {0, 0, 5});

    g3d::vertex v = { 1, 1, 1, 1, 1, 1, 1, 1 };

    theta += 1;
    theta2 += 1;
    if (theta >= fixed(360))
        theta = 0;
    if (theta2 >= fixed(360))
        theta2 = 0;

    for (int i=0; i<36; i+=3)
    {
        rasterize(proj*trans*rot*rot2, vertices[i], vertices[i+1], vertices[i+2], 0, (255/36)*i, 0);
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
