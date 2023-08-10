#pragma once

#include <stdlib.h>
#include "fixed_t.hpp"


struct mat3
{
    fixed *data;
};


struct mat4
{
    fixed *data;

    mat4(fixed f)
    {
        data = (fixed *)malloc(26 * sizeof(fixed));

        for (int i=0; i<16; i++)
        {
            data[i] = 0;
        }

        data[0]  = f;
        data[5]  = f;
        data[10] = f;
        data[15] = f;
    };

};
