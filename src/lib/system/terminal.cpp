#include <system/terminal.hpp>
#include <system/graphics.hpp>
#include <stdlib.h>


uint8_t *   systerm_fontdata;
Terminal    systerm_main_terminal;


int
system::terminal::init( limine_file *fontdata )
{
    systerm_fontdata = (uint8_t *)fontdata->address;
    systerm_main_terminal = terminal_new(graphics::getfb());
    return 0;
}



Terminal
terminal_new( limine_framebuffer *fb )
{
    Terminal t;
    t.data      = (uint8_t *)malloc(2048 * sizeof(uint8_t));
    t.size      = 0;
    t.cursor    = 0;

    t.rcursor   = 0;
    t.rline_num = 0;

    t.fb        = fb;

    return t;
}


static void
f_putchar( Terminal &t, uint64_t char_value )
{
    uint32_t *data = (uint32_t *)(t.fb->address);
    uint8_t  *pixels = &systerm_fontdata[8*8*char_value];

    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (pixels[8*i + j] == 1)
            {
                data[(t.rline_num+i) * (t.fb->pitch / 4) + (t.rcursor + j)] = 0xffffff;
            }
        }
    }

    t.rcursor += 8;
}


void
system::terminal::putchar( Terminal &t, char c )
{
    if (c == 8)
    {
        t.size -= 1;
    }

    else
    {
        t.data[t.size] = c;
        t.size += 1;
    }

    terminal::render(t);
}


void
system::terminal::putstr( Terminal &t, const char *str )
{
    int idx = 0;
    while (str[idx] != '\0')
    {
        system::terminal::putchar(t, str[idx]);
        idx += 1;
    }
}


void
system::terminal::putint( Terminal &t, uint64_t n )
{
    if (n == 0)
    {
        system::terminal::putchar(t, '0');
        return;
    }

    uint64_t i = n;
    uint64_t len = 0;
    while (i > 0)
    {
        i /= 10;
        len += 1;
    }

    char str[64];
    uint64_t idx = len-1;

    while (n > 0)
    {
        uint64_t c = n % 10;
        str[idx] = (char)(c + '0');
        idx -= 1;
        n /= 10;
    }

    str[len] = '\0';
    system::terminal::putstr(t, str);
}


void
system::terminal::clear( Terminal &t )
{
    t.rline_num = 0;
    t.rcursor = 0;

    uint32_t *data = (uint32_t *)t.fb->address;

    for (size_t i=0; i<t.fb->height; i++)
    {
        for (size_t j=0; j<t.fb->width; j++)
        {
            data[i * (t.fb->pitch / 4) + j] = 0x0101010;
        }
    }
}


void
system::terminal::backspc ( Terminal &t )
{
    if (t.size > 0)
        t.size -= 1;
}


void
system::terminal::render( Terminal &t )
{
    system::terminal::clear(t);

    for (size_t i=0; i<t.size; i++)
    {
        switch(t.data[i])
        {
            case ' ':
                t.rcursor += 8;
                break;

            case '\t':
                t.rcursor += 8;
                while (t.rcursor % (23*8) != 0)
                    t.rcursor += 8;
                break;

            case '\n':
                t.rline_num += 16;
                t.rcursor = 0;
                f_putchar(t, ' ');
                break;

            default:
                f_putchar(t, t.data[i]);
                break;
        }
    }

    f_putchar(t, '_');
}



void
system::terminal::putchar( char c )
{
    terminal::putchar( systerm_main_terminal, c );
}

void
system::terminal::putstr( const char *str )
{
    terminal::putstr( systerm_main_terminal, str );
}

void
system::terminal::putint( uint64_t n )
{
    terminal::putint( systerm_main_terminal, n );
}

void
system::terminal::backspc( )
{
    terminal::backspc( systerm_main_terminal );
}





