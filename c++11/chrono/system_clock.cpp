/**
 * system_clock.cpp
 * 2022-06-01 K.OHWADA
 */

//  g++ system_clock.cpp -std=c++11

//reference :  https://cpprefjp.github.io/reference/chrono/system_clock.html

#include <iostream>
#include <chrono>
#include <ctime>

using namespace std::chrono;


/**
 * main
 */
int main()
{
  // get current date and time
  system_clock::time_point p = system_clock::now();

  // convert to time_t and output
  std::time_t t = system_clock::to_time_t(p);
  std::cout << std::ctime(&t) << std::endl;

    return 0;
}


// Mon Aug  8 15:16:41 2022

