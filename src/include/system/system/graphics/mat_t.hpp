#pragma once

#include <stdlib.h>
#include "fixed_t.hpp"
#include "vec_t.hpp"

struct mat3
{
    fixed *data;
};


struct mat4
{
    fixed *data;

    mat4(int32_t n)
    {
        data = (fixed *)malloc(26 * sizeof(fixed));

        for (int i=0; i<16; i++)
        {
            data[i] = 0;
        }

        data[0].data  = n;
        data[5].data  = n;
        data[10].data = n;
        data[15].data = n;
    };

};



vec4 operator * ( const mat4 &A, const vec4 &v );
mat4 operator * ( const mat4 &A, const mat4 &B );
