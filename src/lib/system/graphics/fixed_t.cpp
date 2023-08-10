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
    ab.data = a.data - b.data;
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



fixed fixed_sin( const fixed &f )
{
    /*
        int n = fixed.data >> 16;
        n %= 360;
        return fixed_sin_table[n];
    */

    return 1;
}


fixed fixed_cos( const fixed &f )
{
    /*
        int n = fixed.data >> 16;
        n %= 360;
        return fixed_sin_table[n];
    */

    return 1;
}



