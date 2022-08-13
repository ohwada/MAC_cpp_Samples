/**
 *  sleep_until.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ sleep_until.cpp -std=c++11

// reference : https://cpprefjp.github.io/reference/thread/this_thread/sleep_until.html

#include <thread>
#include <chrono>


/**
 *  main
 */
int main()
{
  auto abs_time = std::chrono::system_clock::now() + std::chrono::seconds(15);
 
  std::this_thread::sleep_until(abs_time);

  return 0;
}
