#pragma once

#include <limine.hpp>

#include "graphics/fixed_t.hpp"
#include "graphics/mat_t.hpp"
#include "graphics/vec_t.hpp"
#include "graphics/vertex.hpp"


namespace g3d
{
    void rasterize( mat4 transform, vertex v0, vertex v1, vertex v2, uint32_t r, uint32_t g, uint32_t b );
};


namespace system::graphics
{
    int     init( limine_framebuffer_response *res );
    void    clear( uint32_t r, uint32_t g, uint32_t b );

    void        swap_buffers();
    uint32_t *  backbuffer( size_t &width, size_t &height, size_t &pitch );

    // limine_framebuffer *getfb();
};

