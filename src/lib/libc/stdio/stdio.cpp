#include <stdio.h>
#include <string.h>
#include <system/terminal.hpp>

limine_framebuffer *        m_framebuffer;
Terminal                    m_terminal;


int
stdio_init( limine_framebuffer_response *res )
{
    if (res == NULL || res->framebuffer_count < 1)
    {
        return 1;
    }

    m_framebuffer = res->framebuffers[0];
    m_terminal    = terminal_new(m_framebuffer);

    return 0;
}


static size_t
internal_printf_num_spec( const char *format )
{
    size_t num_spec = 0;

    for (size_t i=0; i<strlen(format); i++)
        if (format[i] == '%')
            num_spec += 1;

    return num_spec;
}


static void
internal_printf( Terminal &t, char format, va_list args )
{
    switch (format)
    {
    case 'c':
        terminal_putchar(m_terminal, va_arg(args, int));
        break;

    case 's':
        terminal_putstr(m_terminal, va_arg(args, const char *));
        break;

    case 'd':
        terminal_putint(m_terminal, va_arg(args, uint64_t));
        break;
    }
}


int
printf( const char *format, ... )
{
    va_list args;
    size_t num_spec = internal_printf_num_spec(format);

    va_start ( args, num_spec );

    while (*format)
    {
        if (*format == '%')
        {
            format += 1;
            internal_printf(m_terminal, *format, args);
        }

        else
        {
            terminal_putchar(m_terminal, *format);
        }

        format += 1;
    }

    va_end( args );

    return num_spec;
}


