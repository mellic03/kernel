#include "string.h"



size_t
strlen( const char *str )
{
    size_t idx = 0;

    while (str[idx] != '\0')
    {
        idx += 1;
    }

    return idx;
}


int
strcmp( const char *a, const char *b )
{
    size_t alen = strlen(a);
    size_t blen = strlen(b);

    if (alen < blen)
        return -1;

    if (alen > blen)
        return 1;

    while (*a != '\0' && *b != '\0')
    {
        if (*a < *b)
            return -1;

        else if (*a > *b)
            return 1;

        a += 1;
        b += 1;
    }

    return 0;
}


void
strcat( char *dest, const char *src)
{
    size_t len = strlen(dest);

    while (*src)
    {
        dest[len] = *src;
        len += 1;
        src += 1;
    }
}


void
strcpy( char *dest, const char *src )
{
    while (*src)
    {
        *dest = *src;

        dest += 1;
        src += 1;
    }

    *dest = *src;
}
