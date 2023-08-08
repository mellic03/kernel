#include <stdio.h>
#include <system/io.h>


uint8_t
inb( uint16_t port )
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory" );
    return ret;
}


// uint8_t
// inw (uint8_t port)
// {
//     uint8_t ret;
//     asm volatile ( "inw %w1, %0"
//                     :"=a"(ret)
//                     :"Nd"(port) );
//     return ret;
// }



void
outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
}


// void
// outw ( uint8_t port, uint8_t val )
// {
//     asm volatile ("outw %w0,%w1": :"a" (val), "Nd" (port));
// }