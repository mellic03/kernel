#pragma once

#include <stdint.h>
#include "io.h"


enum class PS2EventType
{
    KEY,
    MOUSE
};

enum class PS2KeyEventType
{
    KEY_UP,
    KEY_DOWN,

    NONE
};

enum class PS2MouseEventType
{

};


struct PS2Event
{
    PS2KeyEventType     type;
    uint8_t             data;
};



PS2Event    PS2_poll();
