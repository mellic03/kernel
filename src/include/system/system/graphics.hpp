#pragma once

#include <limine.hpp>
#include <float.h>

struct vec2
{
    union { float x, r; };
    union { float y, g; };
};

struct vec3
{
    union { float x, r; };
    union { float y, g; };
    union { float z, b; };
};

struct vec4
{
    union { float x, r; };
    union { float y, g; };
    union { float z, b; };
    union { float w, a; };
};

struct mat3
{
    float *data;
};

struct mat4
{
    float *data;
};


void rasterize( limine_framebuffer *fb, vec2 v0, vec2 v1, vec2 v2 );

