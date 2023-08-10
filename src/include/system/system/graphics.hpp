#pragma once

#include <limine.hpp>

#include "graphics/fixed_t.hpp"
#include "graphics/mat_t.hpp"
#include "graphics/vec_t.hpp"


void rasterize( limine_framebuffer *fb, vec2 v0, vec2 v1, vec2 v2 );



namespace system::graphics
{
    int     init( limine_framebuffer_response *res );
    void    clear( uint32_t r, uint32_t g, uint32_t b );

    limine_framebuffer *getfb();
};

