#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


struct Terminal
{
    uint8_t *data = nullptr;
    size_t  size;
    size_t  cursor;

    size_t  rline_num;
    size_t  rcursor;
    limine_framebuffer *fb = nullptr;
};

Terminal    terminal_new     ( limine_framebuffer *     );

namespace system::terminal
{
    int         init( limine_file *fontdata );

    void        putchar ( Terminal &, char         );
    void        putstr  ( Terminal &, const char * );
    void        putint  ( Terminal &, uint64_t     );
    void        backspc ( Terminal &               );

    void        putchar ( char         );
    void        putstr  ( const char * );
    void        putint  ( uint64_t     );
    void        backspc (              );

    void        clear   ( Terminal & );
    void        render  ( Terminal & );
};

