/**
 *   sleep_fo.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  sleep_fo.cpp -std=c++11
// https://cpprefjp.github.io/reference/thread/this_thread/sleep_for.html

#include <thread>
#include <chrono>


/**
 *   main
 */
int main()
{
  // block (sleep) the current thread for 3 minutes
  std::this_thread::sleep_for(std::chrono::minutes(3));

  return 0;
}
