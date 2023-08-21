#pragma once

#include <stdlib.h>
#include <initializer_list>

#include "fixed_t.hpp"
#include "vec_t.hpp"


struct mat4
{
    fixed data[16];

    mat4() {  };

    mat4( const fixed &f )
    {
        for (int i=0; i<16; i++)
        {
            data[i].data = 0;
        }

        data[0]  = f;
        data[5]  = f;
        data[10] = f;
        data[15] = f;
    };

    mat4( std::initializer_list<fixed> list )
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

    fixed *operator [] ( int i )
    {
        return &(data[4*i]);
    };

    const fixed *operator [] ( int i ) const
    {
        return &(data[4*i]);
    };

};


vec4 operator * ( const mat4 &A, const vec4 &v );
mat4 operator * ( const mat4 &A, const mat4 &B );


namespace g3d
{
    fixed dot( vec4 u, vec4 v );
    vec4  normalize( vec4 v );

    mat4 perspective( const fixed &fovy, const fixed &aspect, const fixed &zNear, const fixed &zFar );

    mat4 translate( const mat4 &mat, const vec3 &v );
    mat4 rotateX( const mat4 &mat, fixed theta );
    mat4 rotateY( const mat4 &mat, fixed theta );
    mat4 rotateZ( const mat4 &mat, fixed theta );
};
