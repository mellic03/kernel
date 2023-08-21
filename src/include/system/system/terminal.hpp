#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <system/graphics/fixed_t.hpp>

struct Terminal
{
    uint8_t *data = nullptr;
    size_t  size;
    size_t  cursor;

    size_t  rline_num;
    size_t  rcursor;
};

Terminal    terminal_new( );

namespace system::terminal
{
    int         init( limine_file *fontdata );

    void        putchar ( Terminal &, char         );
    void        putstr  ( Terminal &, const char * );
    void        putint  ( Terminal &, int64_t      );
    void        backspc ( Terminal &               );

    void        putchar ( char         );
    void        putstr  ( const char * );
    void        putint  ( int64_t      );
    void        putuint ( uint64_t     );
    void        putfixed( int64_t      );
    void        backspc (              );

    void        render  ( );
};

