/**
 * duration.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ duration.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/chrono/duration.html

#include <iostream>
#include <chrono>
#include <ctime>

using std::chrono::system_clock;
using std::chrono::seconds;


/**
 * print
 */
void print(const system_clock::time_point& p)
{
  std::time_t t = system_clock::to_time_t(p);

// requires at least 26 bytes
  char buf[26]; 
 
  // reentrant version of ctime()
  ctime_r(&t, buf);

  // Note: the output string contains newlines
  std::cout << buf;
}


/**
 * main
 */
int main()
{
  // get current date and time
  system_clock::time_point now = system_clock::now();

  // get the date and time after 3 seconds
  system_clock::time_point p = now + seconds(3);

  print(now);
  print(p);

    return 0;
}


// Mon Aug  8 15:36:17 2022
// Mon Aug  8 15:36:20 2022


