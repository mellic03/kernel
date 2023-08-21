#pragma once

#include <stdint.h>

#define fixed_shift (1 << 10)
#define SHIFT_MASK (fixed_shift - 1)

#define fixed_mult(a, b) (((int64_t)(a) * (int64_t)(b)) / fixed_shift);

#define fixed fixed_t

struct fixed_t
{
    int32_t data;

    fixed_t()
    {
        data = 0;
    };

    fixed_t( const int &n )
    {
        data = n * fixed_shift;
    };

    operator int() const
    {
        return data / fixed_shift;
    };
};



fixed operator + ( const fixed &a, const fixed &b );
fixed operator - ( const fixed &a, const fixed &b );
fixed operator * ( const fixed &a, const fixed &b );
fixed operator / ( const fixed &a, const fixed &b );

fixed &operator += ( fixed &a, const fixed &b );
fixed &operator -= ( fixed &a, const fixed &b );
fixed &operator *= ( fixed &a, const fixed &b );
fixed &operator /= ( fixed &a, const fixed &b );

bool operator <  ( const fixed &a, const fixed &b );
bool operator >  ( const fixed &a, const fixed &b );
bool operator == ( const fixed &a, const fixed &b );
bool operator <= ( const fixed &a, const fixed &b );
bool operator >= ( const fixed &a, const fixed &b );


int   load_fixed_trigtables( int32_t *baseptr );

fixed fixed_sin( const fixed &f );
fixed fixed_cos( const fixed &f );
fixed fixed_tan( const fixed &f );

fixed fixed_abs( const fixed &f );

fixed fixed_sqrt( const fixed &f );

