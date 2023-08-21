#include <system/graphics.hpp>
#include <util/util.hpp>



limine_framebuffer *sysgh_main_fb = nullptr;

size_t      sys_fb_width,  sys_fb_height,  sys_fb_pitch;
size_t      sys_fb_size;

uint32_t *  sys_back_buffer;

fixed *     sys_z_buffer;
size_t      sys_zb_size;



int
system::graphics::init( limine_framebuffer_response *res )
{
    sysgh_main_fb = res->framebuffers[0];

    sys_fb_width  = res->framebuffers[0]->width;
    sys_fb_height = res->framebuffers[0]->height;
    sys_fb_pitch  = res->framebuffers[0]->pitch;

    sys_fb_size = sys_fb_width * sys_fb_height * sizeof(uint32_t);
    sys_zb_size = sys_fb_width * sys_fb_height * sizeof(fixed);

    sys_back_buffer  = (uint32_t *)malloc(sys_fb_size);
    sys_z_buffer = (fixed *)malloc(sys_zb_size);

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

    for (size_t i=0; i< sys_fb_width*sys_fb_height; i++)
    {
        sys_z_buffer[i].data = 1 << 30;
    }
}


vec3 calculate_barycentric( const fixed &x, const fixed &y, const vec4 &p1, const vec4 &p2, const vec4 &p3 )
{
    vec3 weights = { 0, 0, 0 };

    const fixed denom = ((p2.y-p3.y)*(p1.x-p3.x) + (p3.x-p2.x)*(p1.y-p3.y));
    weights.x = ((p2.y-p3.y)*(x-p3.x) + (p3.x-p2.x)*(y-p3.y)) / denom;
    weights.y = ((p3.y-p1.y)*(x-p3.x) + (p1.x-p3.x)*(y-p3.y)) / denom;
    weights.z = fixed(1) - weights.x - weights.y;

    return weights;
};


void cbar_xaxis()
{

}

void cbar_yaxis()
{

}


uint32_t packrgb(uint32_t r, uint32_t g, uint32_t b)
{
    return (r << 16) + (g << 8) + b;
}


int clamp( const int &n, const int &min, const int &max )
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}


void
internal_rasterize( g3d::vertex v0, g3d::vertex v1, g3d::vertex v2, uint32_t r, uint32_t g, uint32_t b )
{
    int xmin = std::min((int)v0.position.x, std::min((int)v1.position.x, (int)v2.position.x));
    int xmax = std::max((int)v0.position.x, std::max((int)v1.position.x, (int)v2.position.x));

    int ymin = std::min((int)v0.position.y, std::min((int)v1.position.y, (int)v2.position.y));
    int ymax = std::max((int)v0.position.y, std::max((int)v1.position.y, (int)v2.position.y));

    xmin = clamp(xmin, 0, 1280-1);  xmax = clamp(xmax, 0, 1280-1);
    ymin = clamp(ymin, 0, 800-1);   ymax = clamp(ymax, 0, 800-1);


    uint32_t *data = sys_back_buffer;
    int idx = 0;


    vec4 dir = { 1, 0, 0, 0 };
    fixed lighting = g3d::dot(v0.normal, dir);
    lighting += 1;
    lighting /= 2;


    for (int y=ymin; y<=ymax; y+=1)
    {
        idx = y * (sys_fb_pitch/4);

        for (int x=xmin; x<=xmax; x+=1)
        {
            vec3 weights = calculate_barycentric(x, y, v0.position, v1.position, v2.position);
            if (weights.x.data < 0 || weights.y.data < 0 || weights.z.data < 0)
                continue;

            fixed z_index = (fixed(1)/v0.position.z)*weights.x + (fixed(1)/v1.position.z)*weights.y + (fixed(1)/v2.position.z)*weights.z;

            if (z_index > sys_z_buffer[idx+x])
                continue;
            
            sys_z_buffer[idx+x] = z_index;

            r = (int)(lighting * fixed(255));
            g = (int)(lighting * fixed(255));
            b = (int)(lighting * fixed(255));

            data[idx+x] = (r << 16) + (g << 8) + b;
        }
    }
}




vec4 &project( vec4 &v )
{
    v.x = fixed(640) * (v.x / v.z) + fixed(640);
    v.y = fixed(400) * (v.y / v.z) + fixed(400);

    return v;
}



void
g3d::rasterize( mat4 transform, vertex v0, vertex v1, vertex v2, uint32_t r, uint32_t g, uint32_t b )
{
    v0.position = transform * v0.position;
    v1.position = transform * v1.position;
    v2.position = transform * v2.position;

    v0.normal = transform * v0.normal;
    v1.normal = transform * v1.normal;
    v2.normal = transform * v2.normal;

    v0.position = project(v0.position);
    v1.position = project(v1.position);
    v2.position = project(v2.position);


    if (g3d::dot(v0.normal, {0, 0, 1, 0}).data > 0)
        internal_rasterize( v0, v1, v2, r, g, b );
}

