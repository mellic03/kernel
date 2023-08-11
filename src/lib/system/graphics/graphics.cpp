#include <system/graphics.hpp>
#include <util/util.hpp>



limine_framebuffer *sysgh_main_fb = nullptr;

size_t      sys_fb_width,  sys_fb_height,  sys_fb_pitch;
size_t      sys_fb_size;

uint32_t *  sys_back_buffer;



int
system::graphics::init( limine_framebuffer_response *res )
{
    sysgh_main_fb = res->framebuffers[0];

    sys_fb_width  = res->framebuffers[0]->width;
    sys_fb_height = res->framebuffers[0]->height;
    sys_fb_pitch  = res->framebuffers[0]->pitch;
    sys_fb_size = sys_fb_width * sys_fb_height * sizeof(uint32_t);

    sys_back_buffer  = (uint32_t *)malloc(sys_fb_size);

    return 0;
}


void
system::graphics::swap_buffers()
{
    memcpy(sysgh_main_fb->address, (void *)sys_back_buffer, sys_fb_size);
    graphics::clear(0, 0, 0);
}


uint32_t *
system::graphics::backbuffer( size_t &width, size_t &height, size_t &pitch )
{
    width  = sys_fb_width;
    height = sys_fb_height;
    pitch  = sys_fb_pitch;
    return sys_back_buffer;
}


void
system::graphics::clear( uint32_t r, uint32_t g, uint32_t b )
{
    memset((void *)sys_back_buffer, (r<<16) + (g<<8) + b, sys_fb_size);
}


vec3 calculate_barycentric( fixed x, fixed y, vec2 p1, vec2 p2, vec2 p3 )
{
    vec3 weights = {0, 0, 0};

    const fixed_t denom = ((p2.y-p3.y)*(p1.x-p3.x) + (p3.x-p2.x)*(p1.y-p3.y));
    weights.x = ((p2.y-p3.y)*(x-p3.x) + (p3.x-p2.x)*(y-p3.y)) / denom;
    weights.y = ((p3.y-p1.y)*(x-p3.x) + (p1.x-p3.x)*(y-p3.y)) / denom;
    weights.z = fixed_t(1) - weights.x - weights.y;

    return weights;
};


uint32_t packrgb(uint32_t r, uint32_t g, uint32_t b)
{
    return (r << 16) + (g << 8) + b;
}


int clamp(int n, int min, int max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}


void rasterize( vec2 v0, vec2 v1, vec2 v2 )
{
    int xmin = std::min((int)v0.x, std::min((int)v1.x, (int)v2.x));
    int xmax = std::max((int)v0.x, std::max((int)v1.x, (int)v2.x));

    int ymin = std::min((int)v0.y, std::min((int)v1.y, (int)v2.y));
    int ymax = std::max((int)v0.y, std::max((int)v1.y, (int)v2.y));

    xmin = clamp(xmin, 0, 700);
    xmax = clamp(xmax, 0, 700);
    ymin = clamp(ymin, 0, 700);
    ymax = clamp(ymax, 0, 700);

    uint32_t *data = sys_back_buffer;

    for (int y=ymin; y<=ymax; y++)
    {
        for (int x=xmin; x<=xmax; x++)
        {
            vec3 weights = calculate_barycentric(x, y, v0, v1, v2);
            if (weights.x.data < 0 || weights.y.data < 0 || weights.z.data < 0)
                continue;
            
            uint32_t r = (weights.x.data * 255) >> 16;
            uint32_t g = (weights.y.data * 255) >> 16;
            uint32_t b = (weights.z.data * 255) >> 16;

            data[y * (sys_fb_pitch / 4) + x] = packrgb(r, g, b);
        }
    }
}



void rasterize( mat4 transform, vec4 v0, vec4 v1, vec4 v2 )
{
    v0 = transform * v0;
    v1 = transform * v1;
    v2 = transform * v2;

    rasterize( {v0.x, v0.y}, {v1.x, v1.y}, {v2.x, v2.y} );
}

