#pragma once

#include <stdlib.h>
#include "fixed_t.hpp"


struct vec3
{
    union { fixed x, r; };
    union { fixed y, g; };
    union { fixed z, b; };
};

struct vec4
{
    union { fixed x, r; };
    union { fixed y, g; };
    union { fixed z, b; };
    union { fixed w, a; };
};


vec4 operator + ( const vec4 &u, const vec4 &v );
vec4 operator - ( const vec4 &u, const vec4 &v );

vec4 &operator += ( vec4 &v, const fixed &f );
vec4 &operator -= ( vec4 &v, const fixed &f );
vec4 &operator *= ( vec4 &v, const fixed &f );
vec4 &operator /= ( vec4 &v, const fixed &f );

vec4 operator - ( vec4 v );
