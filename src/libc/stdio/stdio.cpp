#include "stdio.h"
#include <string.h>


void
stdio_init( limine_framebuffer_response *res )
{

}


int
printf( const char *format, ... )
{
    va_list args;
    size_t idx = 0;
    size_t num_spec = 0;

    for (size_t i=0; i<strlen(format); i++)
    {
        if (format[i] == '%')
            num_spec += 1;
    }


    va_start ( args, num_spec );

    while (format[idx] != '\0')
    {
        if (format[idx] == '%')
        {
            idx += 1;

            if (format[idx] == 'c')
            {
                // terminal_putchar(va_arg(args, int));
            }

            else if (format[idx] == 's')
            {
                // terminal_putstr(va_arg(args, const char *));
            }

            else if (format[idx] == 'd')
            {
                // terminal_putint(va_arg(args, uint64_t));
            }
        }

        else
        {
            // terminal_putchar(format[idx]);
        }

        idx += 1;
    }

    va_end( args );

    return num_spec;
}


