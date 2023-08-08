#pragma once

#include <stdlib.h>
#include <string.h>


namespace std
{
    class string;
};



class std::string
{
private:
    char *              m_data;

public:
                        string();
                        string( const char * );
                        ~string();

    const char *        c_str() const { return m_data; };

};


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


std::string::~string()
{
    free(m_data);
}

