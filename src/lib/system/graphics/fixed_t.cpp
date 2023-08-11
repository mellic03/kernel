#include <system/graphics/fixed_t.hpp>



fixed operator + ( const fixed &a, const fixed &b )
{
    fixed ab(0);
    ab.data = a.data + b.data;
    return ab;
}


fixed operator - ( const fixed &a, const fixed &b )
{
    fixed ab(0);
    ab.data = a.data + ((~b.data) + 1);
    return ab;
}


fixed operator * ( const fixed &a, const fixed &b )
{
    fixed ab(0);
    ab.data = fixed_point_mul(a.data, b.data);
    return ab;
}


fixed operator / ( const fixed &a, const fixed &b )
{
    fixed ab(0);
    ab.data = fixed_point_div(a.data, b.data);
    return ab;
}

fixed &operator += ( fixed &a, const fixed &b )
{
    a.data += b.data;
    return a;
}



// TRIG FUNCTIONS -------------------------------------------------
// ----------------------------------------------------------------
int32_t *fixed_sintable;
int32_t *fixed_costable;
int32_t *fixed_tantable;

int
load_fixed_trigtables( int32_t *baseptr )
{
    fixed_sintable = baseptr;
    fixed_costable = baseptr + 360;
    fixed_tantable = baseptr + 720;

    return 0;
}


fixed
fixed_sin( const fixed &f )
{
    int32_t idx = f.data >> 16;
    idx %= 360;

    fixed sinf(0);
    sinf.data = fixed_sintable[idx];
    return sinf;
}


fixed
fixed_cos( const fixed &f )
{
    int32_t idx = f.data >> 16;
    idx %= 360;

    fixed cosf(0);
    cosf.data = fixed_costable[idx];
    return cosf;
}


// ----------------------------------------------------------------
// ----------------------------------------------------------------

