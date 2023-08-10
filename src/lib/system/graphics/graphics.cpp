#include <system/graphics.hpp>
#include <util/util.hpp>



limine_framebuffer *sysgh_main_fb = nullptr;


int
system::graphics::init( limine_framebuffer_response *res )
{
    sysgh_main_fb = res->framebuffers[0];
    return 0;
}


void
system::graphics::clear( uint32_t r, uint32_t g, uint32_t b )
{
    uint32_t *data = (uint32_t *)(sysgh_main_fb->address);
    size_t width   = sysgh_main_fb->width;
    size_t height  = sysgh_main_fb->height;
    size_t pitch   = sysgh_main_fb->pitch;

    for (size_t i=0; i<width; i++)
    {
        for (size_t j=0; j<height; j++)
        {
            data[i * (pitch / 4) + j] = (r << 16) + (g << 8) + b;
        }
    }
}


limine_framebuffer *
system::graphics::getfb()
{
    return sysgh_main_fb;
}


vec3 calculate_barycentric( int x, int y, vec2 p1, vec2 p2, vec2 p3 )
{
    vec3 weights;

    fixed_t xx(x), yy(y);

    fixed_t p1x(p1.x), p1y(p1.y);
    fixed_t p2x(p2.x), p2y(p2.y);
    fixed_t p3x(p3.x), p3y(p3.y);

    const fixed_t denom = ((p2y-p3y)*(p1x-p3x) + (p3x-p2x)*(p1y-p3y));
    weights.x = ((p2y-p3y)*(xx-p3x) + (p3x-p2x)*(yy-p3y)) / denom;
    weights.y = ((p3y-p1y)*(xx-p3x) + (p1x-p3x)*(yy-p3y)) / denom;
    weights.z = fixed_t(1) - weights.x - weights.y;

    return weights;
};


uint32_t gethex(uint32_t r, uint32_t g, uint32_t b)
{
    return (r << 16) + (g << 8) + b;
}


void rasterize( limine_framebuffer *fb, vec2 v0, vec2 v1, vec2 v2 )
{
    int xmin = std::min(v0.x, std::min(v1.x, v2.x));
    int xmax = std::max(v0.x, std::max(v1.x, v2.x));

    int ymin = std::min(v0.y, std::min(v1.y, v2.y));
    int ymax = std::max(v0.y, std::max(v1.y, v2.y));

    uint32_t *data = (uint32_t *)(fb->address);

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

            data[y * (fb->pitch / 4) + x] = gethex(r, g, b);
        }
    }

}


