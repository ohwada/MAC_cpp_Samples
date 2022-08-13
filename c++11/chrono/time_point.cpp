/**
 * time_point.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ time_point.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/chrono/time_point.html

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using std::chrono::system_clock;


/**
 * main
 */
int main() 
{
  // get current date and time
  system_clock::time_point p = system_clock::now();

  // output
  std::time_t t = system_clock::to_time_t(p);
  const std::tm* lt = std::localtime(&t);
  std::cout << std::put_time(lt, "%c") << std::endl;

    return 0;
}

// Mon Aug  8 16:12:48 2022
