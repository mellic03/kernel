#pragma once

#include <limine.hpp>
#include <stdint.h>
#include <stddef.h>

namespace system::fs
{
    int     init( limine_memmap_response *res );
    void *  get_fast_memory( size_t num_bytes );
    void *  get_memory( size_t num_bytes );
    void    free_memory( void *addr );

};




// namespace system::fs
// {
//     enum class dir_class { FILE, DIR };
//     struct dir_entry;
//     struct file;
// }


// struct system::fs::file
// {
//     size_t  size;
//     void *  base;
// };


// struct system::fs::dir_entry
// {
//     system::fs::dir_class       m_class;
//     std::vector<dir_entry *>    m_children;
//     system::fs::file *          m_file;
// };


