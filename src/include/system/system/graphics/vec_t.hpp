#pragma once

#include <stdlib.h>
#include "fixed_t.hpp"


struct vec2
{
    union { int x, r; };
    union { int y, g; };
};


struct vec3
{
    union { fixed x, r; };
    union { fixed y, g; };
    union { fixed z, b; };
    vec3() {  };
};

struct vec4
{
    union { fixed x, r; };
    union { fixed y, g; };
    union { fixed z, b; };
    union { fixed w, a; };
};