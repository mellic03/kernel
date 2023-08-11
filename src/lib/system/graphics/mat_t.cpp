#include <system/graphics/mat_t.hpp>


vec2 operator * ( const mat2 &A, const vec2 &v )
{
    vec2 Av = { 0, 0 };

    Av.x = v.x*A.data[0] + v.y*A.data[1];
    Av.y = v.x*A.data[2] + v.y*A.data[3];

    return Av;
}



vec4 operator * ( const mat4 &A, const vec4 &v )
{
    vec4 Av = { 0, 0, 0, 0 };

    Av.x = v.x*A.data[4*0+0] + v.y*A.data[4*0+1] + v.z*A.data[4*0+2] + v.w*A.data[4*0+3];
    Av.y = v.x*A.data[4*1+0] + v.y*A.data[4*1+1] + v.z*A.data[4*1+2] + v.w*A.data[4*1+3];
    Av.z = v.x*A.data[4*2+0] + v.y*A.data[4*2+1] + v.z*A.data[4*2+2] + v.w*A.data[4*2+3];
    Av.w = v.w;

    return Av;
}


mat4 operator * ( const mat4 &A, const mat4 &B )
{
    mat4 AB(0);

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            AB.data[4*i+j] = 0;

            for (int k=0; k<4; k++)
                AB.data[4*i+j] += A.data[4*i+k] * B.data[4*k+j];
        }
    }

    return AB;
}


mat2 operator * ( const mat2 &A, const mat2 &B )
{
    mat2 AB(0);

    for (int i=0; i<2; i++)
    {
        for (int j=0; j<2; j++)
        {
            AB.data[2*i+j] = 0;

            for (int k=0; k<2; k++)
                AB.data[2*i+j] += A.data[2*i+k] * B.data[2*k+j];
        }
    }

    return AB;
}


mat2
g3d::translate( const mat2 &mat, const vec2 &v )
{
    mat2 out(mat);

    out.data[1]  += v.x;
    out.data[3]  += v.y;

    return out;
}


mat4
g3d::rotate( const mat4 &mat, fixed theta )
{
    mat4 out(mat);

    fixed sintheta = fixed_sin(theta);
    fixed costheta = fixed_cos(theta);


    // mat2 rot {
    //     costheta,  fixed(0) - sintheta,
    //     sintheta,  costheta
    // };


    // mat4 rotx {
    //     1,      0,          0,          0,
    //     0,      costheta,   sintheta,   0,
    //     0,     -sintheta,   costheta,   0,
    //     0,      0,          0,          1
    // };

    // mat4 roty {
    //     costheta,   0,     -sintheta,   0,
    //     0,          1,      0,          0,
    //     sintheta,   0,      costheta,   0,
    //     0,          0,      0,          1
    // };

    mat4 rotz {
        costheta, fixed(0)-sintheta,  0,      0,
        sintheta,  costheta,  0,      0,
        0,         0,         1,      0,
        0,         0,         0,      1
    };

    return rotz;
}


mat4
g3d::translate( const mat4 &mat, const vec3 &v )
{
    mat4 out(1<<16);

    out.data[3]  += v.x;
    out.data[7]  += v.y;
    out.data[11] += v.z;

    return out;
}


fixed
g3d::dot( const vec4 &u, const vec4 &v )
{
    return u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w;
}


mat4
g3d::perspective( fixed fovy, fixed aspect, fixed zNear, fixed zFar )
{
    
}
