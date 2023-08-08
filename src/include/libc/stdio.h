#pragma once

#include <stdarg.h>
#include <limine.hpp>
#include <system.hpp>

// #include "terminal/terminal.hpp"
// #include "device/device.h"


int     stdio_init( limine_framebuffer_response *res );

int     printf( const char *format, ... );



