#include <system/graphics/mat_t.hpp>



vec4 operator * ( const mat4 &A, const vec4 &v )
{
    vec4 Av { 0, 0, 0, 0 };

    Av.x = v.x*A.data[4*0+0] + v.y*A.data[4*0+1] + v.z*A.data[4*0+2] + v.w*A.data[4*0+3];
    Av.y = v.x*A.data[4*1+0] + v.y*A.data[4*1+1] + v.z*A.data[4*1+2] + v.w*A.data[4*1+3];
    Av.z = v.x*A.data[4*2+0] + v.y*A.data[4*2+1] + v.z*A.data[4*2+2] + v.w*A.data[4*2+3];
    Av.w = v.x*A.data[4*3+0] + v.y*A.data[4*3+1] + v.z*A.data[4*3+2] + v.w*A.data[4*3+3];

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
            {

            }
        }
    }


    return AB;
}
