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
    ab.data = ((int64_t)(a.data) * (int64_t)(b.data)) / fixed_shift;
    return ab;
}


fixed operator / ( const fixed &a, const fixed &b )
{
    fixed ab(0);
    if (b.data == 0)
        ab.data = ((int64_t)(a.data) * fixed_shift) / ((int64_t)b.data+1);
    else
        ab.data = ((int64_t)(a.data) * fixed_shift) / (int64_t)b.data;
    return ab;
}


fixed &operator += ( fixed &a, const fixed &b )
{
    a = a + b;
    return a;
}


fixed &operator -= ( fixed &a, const fixed &b )
{
    a = a - b;
    return a;
}


fixed &operator *= ( fixed &a, const fixed &b )
{
    a = a * b;
    return a;
}


fixed &operator /= ( fixed &a, const fixed &b )
{
    a = a / b;
    return a;
}


bool operator <  ( const fixed &a, const fixed &b )
{
    return a.data < b.data;
}


bool operator >  ( const fixed &a, const fixed &b )
{
    return a.data > b.data;
}


bool operator == ( const fixed &a, const fixed &b )
{
    return a.data == b.data;
}


bool operator <= ( const fixed &a, const fixed &b )
{
    return a.data <= b.data;
}


bool operator >= ( const fixed &a, const fixed &b )
{
    return a.data >= b.data;
}




// TRIG FUNCTIONS -------------------------------------------------
// ----------------------------------------------------------------
int32_t *fixed_sintable;
int32_t *fixed_tantable;

int
load_fixed_trigtables( int32_t *baseptr )
{
    fixed_sintable = baseptr + 0*720;
    fixed_tantable = baseptr + 1*720;
    return 0;
}


fixed fixed_trig( const fixed &f, int32_t *trigtable )
{
    int idx = (int)(f*(fixed(2)));
    if (idx < 0)
        idx = -idx;
    
    idx %= 720;

    fixed trigf(0);
    trigf.data = trigtable[idx];
    return trigf;
}


fixed
fixed_sin( const fixed &f )
{
    return fixed_trig(f, fixed_sintable);
}


fixed
fixed_cos( const fixed &f )
{
    return fixed_sin(f + fixed(90));
}


fixed
fixed_tan( const fixed &f )
{
    return fixed_trig(f, fixed_tantable);
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------


fixed fixed_abs( const fixed &f )
{
    if (f.data < 0)
        return fixed(0) - f;
    return f;
}


bool fixed_equal( const fixed &a, const fixed &b )
{
    fixed epsilon = fixed(1) / fixed(5);
    fixed c = fixed_abs(a-b);
    return c.data < epsilon.data;
}


fixed
fixed_sqrt( const fixed &f )
{
    fixed left = 0;
    fixed right = f;

    const fixed half = fixed(1) / fixed(2);
    const fixed tenth = fixed(1) / fixed(10);

    while (left <= right)
    {
        fixed mid = (left + right) / fixed(2);

        for (fixed i=mid-half; i<mid+half; i+=tenth)
        {
            if (fixed_equal(i*i, f))
                return i;
        }

        if (mid*mid < f)
        {
            left = mid + fixed(1);
        }
        
        else if (mid*mid > f)
        {
            right = mid;
        }
    }

}
