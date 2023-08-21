#include <system/graphics/mat_t.hpp>


vec4 operator * ( const mat4 &A, const vec4 &v )
{
    vec4 Av = { 0, 0, 0, 0 };

    Av.x = (v.x*A[0][0]) + (v.y*A[0][1]) + (v.z*A[0][2]) + (v.w*A[0][3]);
    Av.y = (v.x*A[1][0]) + (v.y*A[1][1]) + (v.z*A[1][2]) + (v.w*A[1][3]);
    Av.z = (v.x*A[2][0]) + (v.y*A[2][1]) + (v.z*A[2][2]) + (v.w*A[2][3]);
    Av.w = (v.x*A[3][0]) + (v.y*A[3][1]) + (v.z*A[3][2]) + (v.w*A[3][3]);

    return Av;
}


mat4 operator * ( const mat4 &A, const mat4 &B )
{
    mat4 AB(fixed(1));

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            AB[i][j] = 0;

            for (int k=0; k<4; k++)
                AB[i][j] = AB[i][j] + (A[i][k] * B[k][j]);
        }
    }

    return AB;
}


mat4
g3d::rotateX( const mat4 &mat, fixed theta )
{
    mat4 out(mat);

    fixed sintheta = fixed_sin(theta);
    fixed costheta = fixed_cos(theta);

    mat4 rotx {
        1,      0,                   0,          0,
        0,      costheta,            sintheta,   0,
        0,      fixed(0)-sintheta,   costheta,   0,
        0,      0,                   0,          1
    };

    return rotx;
}


mat4
g3d::rotateY( const mat4 &mat, fixed theta )
{
    mat4 out(mat);

    fixed sintheta = fixed_sin(theta);
    fixed costheta = fixed_cos(theta);

    mat4 roty {
        costheta,   0,      fixed(0)-sintheta,   0,
        0,          1,      0,                   0,
        sintheta,   0,      costheta,            0,
        0,          0,      0,                   1
    };

    return roty;
}


mat4
g3d::rotateZ( const mat4 &mat, fixed theta )
{
    mat4 out(mat);

    fixed sintheta = fixed_sin(theta);
    fixed costheta = fixed_cos(theta);

    mat4 rotz {
        costheta,  fixed(0)-sintheta,  0,      0,
        sintheta,  costheta,           0,      0,
        0,         0,                  1,      0,
        0,         0,                  0,      1
    };

    return rotz;
}


mat4
g3d::translate( const mat4 &mat, const vec3 &v )
{
    mat4 out(1);

    out.data[3]  += v.x;
    out.data[7]  += v.y;
    out.data[11] += v.z;

    return out;
}


fixed
g3d::dot( vec4 u, vec4 v )
{
    return (u.x*v.x) + (u.y*v.y) + (u.z*v.z);
}


vec4
g3d::normalize( vec4 v )
{
    fixed magSq = v.x*v.x + v.y*v.y + v.z*v.z;
    fixed mag = fixed_sqrt(magSq);

    v.x /= mag;
    v.y /= mag;
    v.z /= mag;

    return v;
}


mat4
g3d::perspective( const fixed &fovy, const fixed &aspect, const fixed &zNear, const fixed &zFar )
{
    mat4 out(0);

    fixed tanHalfFovy = fixed_tan(fovy / fixed(2));

    out[0][0] = fixed(1) / (aspect * tanHalfFovy);
    out[1][1] = fixed(1) / tanHalfFovy;
    out[2][2] = fixed(0) - ((zFar + zNear) / (zFar - zNear));
    out[2][3] = fixed(0) - fixed(1);
    out[3][2] = fixed(0) - ((fixed(2) * zFar * zNear) / (zFar - zNear));

    return out;
}



