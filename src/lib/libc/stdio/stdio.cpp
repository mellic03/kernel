#include <stdio.h>
#include <string.h>
#include <system/terminal.hpp>



static size_t
num_format_specs( const char *format )
{
    size_t num_spec = 0;

    while (*format)
    {
        if (*format == '%')
        {
            num_spec += 1;
            format += 1;
        }
        format += 1;
    }

    return num_spec;
}


static void
internal_printf( char format, va_list args )
{
    switch (format)
    {
    case 'c':
        system::terminal::putchar(va_arg(args, int));
        break;

    case 's':
        system::terminal::putstr(va_arg(args, const char *));
        break;

    case 'd':
        system::terminal::putint(va_arg(args, uint64_t));
        break;
    }
}


int
printf( const char *format, ... )
{
    va_list args;
    size_t num_spec = num_format_specs(format);

    va_start ( args, num_spec );

    while (*format)
    {
        if (*format == '%')
        {
            format += 1;
            internal_printf(*format, args);
        }

        else
        {
            system::terminal::putchar(*format);
        }

        format += 1;
    }

    va_end( args );

    return num_spec;
}


