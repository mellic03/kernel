#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>



struct Terminal
{
    char *data;
    uint32_t size;
    uint32_t cursor;

    uint32_t rline_num;
    uint32_t rcursor;

    limine_framebuffer *fb;
};


Terminal    terminal_new     ( limine_framebuffer *     );

void        terminal_putchar ( Terminal &, char         );
void        terminal_putstr  ( Terminal &, const char * );
void        terminal_putint  ( Terminal &, uint64_t     );
void        terminal_backspc ( Terminal &               );

void        terminal_clear   ( Terminal & );
void        terminal_render  ( Terminal & );

void        terminal_put ( Terminal &, char         );
void        terminal_put ( Terminal &, const char * );
void        terminal_put ( Terminal &, uint64_t     );

void        terminal_printf( Terminal &t, const char *format, ... );


