#include <stdlib.h>
#include <x86intrin.h>


void *memcpy( void *dest, const void *src, size_t n )
{
    size_t numChunks = n / 16; // Assuming SSE can copy 16 bytes at a time
    size_t remainder = n % 16;

    // Copy chunks using SSE
    const __m128i* srcPtr = reinterpret_cast<const __m128i*>(src);
    __m128i* destPtr = reinterpret_cast<__m128i*>(dest);

    for (size_t i = 0; i < numChunks; ++i)
    {
        __m128i data = _mm_load_si128(srcPtr + i);
        _mm_store_si128(destPtr + i, data);
    }

    // Copy the remaining bytes
    const uint8_t* srcRemainder = reinterpret_cast<const uint8_t*>(src) + numChunks * 16;
    uint8_t* destRemainder = reinterpret_cast<uint8_t*>(dest) + numChunks * 16;

    for (size_t i = 0; i < remainder; ++i)
    {
        destRemainder[i] = srcRemainder[i];
    }

    return dest;
}



// void *memcpy(void *dest, const void *src, size_t n)
// {
//     uint8_t *pdest = (uint8_t *)dest;
//     const uint8_t *psrc = (const uint8_t *)src;
 
//     for (size_t i = 0; i < n; i++)
//     {
//         pdest[i] = psrc[i];
//     }

//     return dest;
// }


void *memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;
 
    for (size_t i = 0; i < n; i++)
    {
        p[i] = (uint8_t)c;
    }
 
    return s;
}


void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;
 
    if (src > dest)
    {
        for (size_t i = 0; i < n; i++)
        {
            pdest[i] = psrc[i];
        }
    }

    else if (src < dest)
    {
        for (size_t i = n; i > 0; i--)
        {
            pdest[i-1] = psrc[i-1];
        }
    }
 
    return dest;
}


int memcmp(const void *s1, const void *s2, size_t n)
{
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;
 
    for (size_t i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }
 
    return 0;
}

