/**
 * tm.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ tm.cpp
// reference : https://en.cppreference.com/w/cpp/chrono/c/tm

#include <ctime>
#include <iostream>
 

/**
 * main
 */
int main()
{
    std::tm tm;
    tm.tm_year = 2022-1900;
    tm.tm_mday = 1;
 
    std::mktime(&tm);
    std::cout << std::asctime(&tm)
              << "sizeof(std::tm) = "
              << sizeof(std::tm) << '\n';

    return 0;
}

// Sat Jan  1 00:01:00 2022
// sizeof(std::tm) = 56
