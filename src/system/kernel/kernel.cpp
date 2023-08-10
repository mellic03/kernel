#include <system.hpp>
#include <system/asm.hpp>
#include "../OS/os.hpp"


extern "C"
void main( void )
{
    int sys_status = kernel_init();
    int os_status = os_init();


    while (1)
    {
        /*
            pre-frame setup

        */

        // OS main loop ----------
        os_status = os_mainloop();
        // -----------------------

        /*
            end-frame processing

        */
    }
}

