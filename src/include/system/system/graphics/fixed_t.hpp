#pragma once

#include <stdint.h>

#define fixed fixed_t
#define fixed_point_add(a,b)  (a+b)
#define fixed_point_sub(a, b)  (a-b)
#define fixed_point_mul(a, b)  (int32_t)(((int64_t)a*(int64_t)b)>>16)
#define fixed_point_div(a, b)  (int32_t)(((int64_t)a<<16)/b)

struct fixed_t
{
    int32_t data;

    fixed_t(int n)
    {
        data = n << 16;
    };

    operator int()
    {
        return data >> 16;
    };

};

fixed operator + ( const fixed &a, const fixed &b );
fixed operator - ( const fixed &a, const fixed &b );
fixed operator * ( const fixed &a, const fixed &b );
fixed operator / ( const fixed &a, const fixed &b );


