/**
 *   mktime.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  mktime.cpp
// reference : https://en.cppreference.com/w/cpp/chrono/c/mktime

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
 

/**
 *   main
 */
int main()
{
    setenv("TZ", "/usr/share/zoneinfo/America/Los_Angeles", 1); // POSIX-specific
 
    std::tm tm;  // zero initialise
    tm.tm_year = 2020-1900; // 2020
    tm.tm_mon = 2-1; // February
    tm.tm_mday = 15; // 15th
    tm.tm_hour = 10;
    tm.tm_min = 15;
    tm.tm_isdst = 0; // Not daylight saving
    std::time_t t = std::mktime(&tm); 
    std::tm local = *std::localtime(&t);
 
    std::cout << "local: " << std::put_time(&local, "%c %Z") << '\n';

    return 0;
}

// local: Sat Feb 15 10:15:00 2020 PST
