#pragma once

#include <stdint.h>

#define fixed fixed_t
#define fixed_point_add(a,b)   (a+b)
#define fixed_point_sub(a, b)  (a-b)
#define fixed_point_mul(a, b)  (int32_t)(((int64_t)a*(int64_t)b)>>16)
#define fixed_point_div(a, b)  (int32_t)(((int64_t)a<<16)/b)


struct fixed_t
{
    int32_t data;

    fixed_t()
    {
        data = 0;
    };

    fixed_t(int n)
    {
        if (n < 0)
            data = -(-n << 16);
        else
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

fixed &operator += ( fixed &a, const fixed &b );



int   load_fixed_trigtables( int32_t *baseptr );

fixed fixed_sin( const fixed &f );
fixed fixed_cos( const fixed &f );




