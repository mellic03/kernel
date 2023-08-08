#include <system/graphics.hpp>
#include <util/util.hpp>

#include <x86intrin.h>


vec3 calculate_barycentric( float x, float y, vec2 p1, vec2 p2, vec2 p3 )
{
    vec3 weights;

    const float denom = (p2.y-p3.y)*(p1.x-p3.x) + (p3.x-p2.x)*(p1.y-p3.y);
    weights.x = ((p2.y-p3.y)*(x-p3.x) + (p3.x-p2.x)*(y-p3.y)) / denom;
    weights.y = ((p3.y-p1.y)*(x-p3.x) + (p1.x-p3.x)*(y-p3.y)) / denom;
    weights.z = 1.0f - weights.x - weights.y;

    return weights;
};


uint32_t gethex(uint32_t r, uint32_t g, uint32_t b)
{
    return (r << 16) + (g << 8) + b;
}


void rasterize( limine_framebuffer *fb, vec2 v0, vec2 v1, vec2 v2 )
{
    float xmin = std::min(v0.x, std::min(v1.x, v2.x));
    float xmax = std::max(v0.x, std::max(v1.x, v2.x));

    float ymin = std::min(v0.y, std::min(v1.y, v2.y));
    float ymax = std::max(v0.y, std::max(v1.y, v2.y));

    __m128 reg1 = _mm_set1_ps(1.0f);

    uint32_t *data = (uint32_t *)(fb->address);

    vec3 weights;

    for (int y=ymin; y<=ymax; y++)
    {
        for (int x=xmin; x<=xmax; x++)
        {
            vec3 weights = calculate_barycentric(x, y, v0, v1, v2);
            if (weights.x < 0.0f || weights.y < 0.0f || weights.z < 0.0f)
                continue;
            
            uint32_t r = 255 * weights.x;
            uint32_t g = 255 * weights.y;
            uint32_t b = 255 * weights.z;

            data[((int)y) * (fb->pitch / 4) + ((int)x)] = gethex(r, g, b);
        }
    }

}

