#pragma once

#include <stdint.h>
#include <stddef.h>


uint8_t         inb ( uint16_t port );
// uint8_t         inw ( uint16_t port );


void            outb( uint16_t port, uint8_t val );
// void            outw( uint16_t port, uint8_t val );



