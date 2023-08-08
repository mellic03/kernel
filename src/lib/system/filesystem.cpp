#include <system/filesystem.hpp>
#include <stddef.h>


limine_module_response *    m_module_res;
limine_file *               m_main_memory;


int
filesystem_init( limine_module_response *res )
{
    m_module_res = res;

    if (res == NULL)
    {
        return 1;
    }

    m_main_memory = res->modules[1];




    return 0;
}


limine_file *
getfs()
{
    return m_main_memory;
}
