#include <system/graphics/vec_t.hpp>



vec4 operator + ( const vec4 &u, const vec4 &v )
{
    vec4 uv = { u.x+v.x, u.y+v.x, u.z+v.z, u.w+v.w };
    return uv;
}


vec4 operator - ( const vec4 &u, const vec4 &v )
{
    vec4 uv = { u.x-v.x, u.y-v.x, u.z-v.z, u.w-v.w };
    return uv;
}


vec4 &operator += ( vec4 &v, const fixed &f )
{
    v.x = v.x + f;
    v.y = v.y + f;
    v.z = v.z + f;
    return v;
}


vec4 &operator -= ( vec4 &v, const fixed &f )
{
    v.x = v.x - f;
    v.y = v.y - f;
    v.z = v.z - f;
    return v;
}


vec4 &operator *= ( vec4 &v, const fixed &f )
{
    v.x = v.x * f;
    v.y = v.y * f;
    v.z = v.z * f;
    v.w = v.w * f;
    return v;
}


vec4 &operator /= ( vec4 &v, const fixed &f )
{
    v.x = v.x / f;
    v.y = v.y / f;
    v.z = v.z / f;
    v.w = v.w / f;
    return v;
}


vec4 operator - ( vec4 v )
{
    v.x = fixed(0) - v.x;
    v.y = fixed(0) - v.y;
    v.z = fixed(0) - v.z;
    v.w = fixed(0) - v.w;
    return v;
}
