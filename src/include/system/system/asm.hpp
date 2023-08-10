#pragma once

#include <stdint.h>


namespace system
{
    /** Halt and catch fire */
    void        hcf( void );

    /** Get tickrate of CPU */
    uint64_t    tickrate( void );

};


