#pragma once



enum class Sys_stat
{
    UNINITIALIZED,
    GOOD,
    BAD
};

limine_framebuffer *getfb();

Sys_stat system_init();



