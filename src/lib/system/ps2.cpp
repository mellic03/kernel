#include <stdio.h>
#include <system/ps2.h>


PS2Event
PS2_poll()
{
    uint8_t opcode = inb(0x60);

    if (opcode > 0x80)
        return { PS2KeyEventType::KEY_UP, '\0' };

    switch (opcode)
    {
        case 0x1C:  return { PS2KeyEventType::KEY_DOWN, '\n' };
        case 0x39:  return { PS2KeyEventType::KEY_DOWN, ' ' };
        case 0x0E:  return { PS2KeyEventType::KEY_DOWN, 8 };
        case 0x8E:  return { PS2KeyEventType::KEY_UP,   8 };

        case 0x9C:  return { PS2KeyEventType::KEY_UP,   '\n' };
        case 0xB9:  return { PS2KeyEventType::KEY_UP,   ' ' };

        case 0x34:  return { PS2KeyEventType::KEY_DOWN, '.' };
        case 0xB4:  return { PS2KeyEventType::KEY_UP,   '.' };


        case 0x01:  return { PS2KeyEventType::KEY_DOWN, '\0' };
        case 0x02:  return { PS2KeyEventType::KEY_DOWN, '1' };
        case 0x03:  return { PS2KeyEventType::KEY_DOWN, '2' };
        case 0x04:  return { PS2KeyEventType::KEY_DOWN, '3' };
        case 0x05:  return { PS2KeyEventType::KEY_DOWN, '4' };
        case 0x06:  return { PS2KeyEventType::KEY_DOWN, '5' };
        case 0x07:  return { PS2KeyEventType::KEY_DOWN, '6' };
        case 0x08:  return { PS2KeyEventType::KEY_DOWN, '7' };
        case 0x09:  return { PS2KeyEventType::KEY_DOWN, '8' };
        case 0x0A:  return { PS2KeyEventType::KEY_DOWN, '9' };
        case 0x0B:  return { PS2KeyEventType::KEY_DOWN, '0' };

        case 0x81:  return { PS2KeyEventType::KEY_UP, '\0' };
        case 0x82:  return { PS2KeyEventType::KEY_UP, '1' };
        case 0x83:  return { PS2KeyEventType::KEY_UP, '2' };
        case 0x84:  return { PS2KeyEventType::KEY_UP, '3' };
        case 0x85:  return { PS2KeyEventType::KEY_UP, '4' };
        case 0x86:  return { PS2KeyEventType::KEY_UP, '5' };
        case 0x87:  return { PS2KeyEventType::KEY_UP, '6' };
        case 0x88:  return { PS2KeyEventType::KEY_UP, '7' };
        case 0x89:  return { PS2KeyEventType::KEY_UP, '8' };
        case 0x8A:  return { PS2KeyEventType::KEY_UP, '9' };
        case 0x8B:  return { PS2KeyEventType::KEY_UP, '0' };


        case 0x10:  return { PS2KeyEventType::KEY_DOWN, 'q' };
        case 0x11:  return { PS2KeyEventType::KEY_DOWN, 'w' };
        case 0x12:  return { PS2KeyEventType::KEY_DOWN, 'e' };
        case 0x13:  return { PS2KeyEventType::KEY_DOWN, 'r' };
        case 0x14:  return { PS2KeyEventType::KEY_DOWN, 't' };
        case 0x15:  return { PS2KeyEventType::KEY_DOWN, 'y' };
        case 0x16:  return { PS2KeyEventType::KEY_DOWN, 'u' };
        case 0x17:  return { PS2KeyEventType::KEY_DOWN, 'i' };
        case 0x18:  return { PS2KeyEventType::KEY_DOWN, 'o' };
        case 0x19:  return { PS2KeyEventType::KEY_DOWN, 'p' };
        // case 0x0A:  return { PS2EventType::KEY_DOWN, 'p' };
        // case 0x0B:  return { PS2EventType::KEY_DOWN, 'p' };
        // case 0x0C:  return { PS2EventType::KEY_DOWN, 'p' };
        // case 0x0D:  return { PS2EventType::KEY_DOWN, 'p' };
        case 0x1E:  return { PS2KeyEventType::KEY_DOWN, 'a' };
        case 0x1F:  return { PS2KeyEventType::KEY_DOWN, 's' };
        case 0x20:  return { PS2KeyEventType::KEY_DOWN, 'd' };
        case 0x21:  return { PS2KeyEventType::KEY_DOWN, 'f' };
        case 0x22:  return { PS2KeyEventType::KEY_DOWN, 'g' };
        case 0x23:  return { PS2KeyEventType::KEY_DOWN, 'h' };
        case 0x24:  return { PS2KeyEventType::KEY_DOWN, 'j' };
        case 0x25:  return { PS2KeyEventType::KEY_DOWN, 'k' };
        case 0x26:  return { PS2KeyEventType::KEY_DOWN, 'l' };
        // case 0x27:  return { PS2EventType::KEY_DOWN, ';' };
        case 0x2C:  return { PS2KeyEventType::KEY_DOWN, 'z' };
        case 0x2D:  return { PS2KeyEventType::KEY_DOWN, 'x' };
        case 0x2E:  return { PS2KeyEventType::KEY_DOWN, 'c' };
        case 0x2F:  return { PS2KeyEventType::KEY_DOWN, 'v' };
        case 0x30:  return { PS2KeyEventType::KEY_DOWN, 'b' };
        case 0x31:  return { PS2KeyEventType::KEY_DOWN, 'n' };
        case 0x32:  return { PS2KeyEventType::KEY_DOWN, 'm' };

        case 0x33:  return { PS2KeyEventType::KEY_DOWN, ',' };

    }


    return { PS2KeyEventType::NONE, '\0' };
}
