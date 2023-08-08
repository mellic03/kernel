#include <string.hpp>

#include <stdlib.h>
#include <string.h>


std::string::string()
{
    m_data = (char *)malloc(1*sizeof(char));
}


std::string::string( const char *str )
{
    size_t len = strlen(str);
    m_data = (char *)malloc(len * sizeof(char));
    strcpy(m_data, str);
}


// std::string::~string()
// {
//     // free(m_data);
// }

