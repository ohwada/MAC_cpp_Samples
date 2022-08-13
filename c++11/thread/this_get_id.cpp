/**
 *  this_get_id.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ this_get_id.cpp -std=c++11
// https://cpprefjp.github.io/reference/thread/this_thread/get_id.html

#include <iostream>
#include <thread>


/**
 *  main
 */
int main()
{
  std::cout << "thread_id=" << std::this_thread::get_id() << std::endl;
  return 0;
}

// thread_id=0x1119ecdc0
