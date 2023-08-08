#pragma once

#include <stdarg.h>
#include <limine.hpp>

#include "terminal/terminal.hpp"
#include "device/device.h"


void stdio_init( limine_framebuffer_response *res );


int printf( const char *format, ... );



