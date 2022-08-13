/**
 *  strftime.cpp
 * 2022-06-01 K.OHWADA
 */

//  g++ strftime.cpp -std=c++11

// reference: https://en.cppreference.com/w/cpp/chrono/c/strftime

#include <iostream>
 #include <chrono>
#include <ctime>
#include <locale>

using namespace std::chrono;


/**
 *  main
 */
int main()
{
    const size_t BUFSIZE = 256;
    char buf[BUFSIZE];

// RFC 822
// (wday), dd MMM YYYY HH:mm:ss +0900
// Thu, 04 Apr 2014 12:35:20 +0900
    const char* FORMAT = "%a, %d %b %Y %H:%M:%S %z";


    system_clock::time_point p = system_clock::now();

    std::time_t t = system_clock::to_time_t(p);

    if (std::strftime(buf, BUFSIZE, FORMAT, std::localtime(&t))) 
    {
        std::cout << buf << std::endl;
    }

    std::locale::global(std::locale("ja_JP.UTF-8"));
    if (std::strftime(buf,  BUFSIZE, FORMAT, std::localtime(&t))) {
        std::cout << buf << std::endl;
    }

    return 0;
}


// Thu, 11 Aug 2022 21:38:18 +0900
// 木, 11  8 2022 21:38:18 +0900

