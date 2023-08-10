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


