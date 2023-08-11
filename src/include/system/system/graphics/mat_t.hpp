#pragma once

#include <stdlib.h>
#include <initializer_list>

#include "fixed_t.hpp"
#include "vec_t.hpp"



struct mat2
{
    fixed data[4];

    mat2() {  };

    mat2(int32_t n)
    {
        for (int i=0; i<4; i++)
        {
            data[i] = 0;
        }

        data[0].data  = n;
        data[3].data  = n;
    };

    mat2(std::initializer_list<fixed> list)
    {
        for (size_t i=0; i<4; i++)
        {
            data[i] = *(list.begin() + i);
        }
    };

    mat2( const mat2 &mat )
    {
        for (size_t i=0; i<4; i++)
        {
            data[i] = mat.data[i];
        }
    };

};


struct mat3
{
    fixed *data;
};


struct mat4
{
    fixed data[16];

    mat4() {  };

    mat4(int32_t n)
    {
        for (int i=0; i<16; i++)
        {
            data[i] = 0;
        }

        data[0].data  = n;
        data[5].data  = n;
        data[10].data = n;
        data[15].data = n;
    };

    mat4(std::initializer_list<fixed> list)
    {
        for (size_t i=0; i<16; i++)
        {
            data[i] = *(list.begin() + i);
        }
    };

    mat4( const mat4 &mat )
    {
        for (size_t i=0; i<16; i++)
        {
            data[i] = mat.data[i];
        }
    };

};


vec2 operator * ( const mat2 &A, const vec2 &v );
mat2 operator * ( const mat2 &A, const mat2 &B );


vec4 operator * ( const mat4 &A, const vec4 &v );
mat4 operator * ( const mat4 &A, const mat4 &B );


namespace g3d
{
    mat2 translate( const mat2 &mat, const vec2 &v );


    fixed dot( const vec4 &u, const vec4 &v );

    mat4 perspective( fixed fovy, fixed aspect, fixed zNear, fixed zFar );

    mat4 translate( const mat4 &mat, const vec3 &v );
    mat4 rotate( const mat4 &mat, fixed theta );
};
