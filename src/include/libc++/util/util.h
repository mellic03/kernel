#pragma once



namespace std
{
    template <typename T>
    T min( T a, T b );

    template <typename T>
    T max( T a, T b );
};


template <typename T>
T
std::min( T a, T b )
{
    if (a < b)
        return a;
    return b;
}


template <typename T>
T
std::max( T a, T b )
{
    if (a > b)
        return a;
    return b;
}
