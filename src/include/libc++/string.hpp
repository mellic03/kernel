#pragma once

#include <stdlib.h>

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
                        ~string()
                        {
                            free(m_data);
                        };

    const char *        c_str() const { return m_data; };

};
