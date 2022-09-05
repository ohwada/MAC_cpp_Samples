/**
 *  time_t.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  time_t.cpp
// reference : https://cpprefjp.github.io/reference/ctime/time_t.html

#include <ctime>
#include <iostream>


/**
 *  main
 */
int main()
{
  
// check the number of bits
  std::cout << sizeof(std::time_t) * 8 << std::endl;

// Get the current date and time 
// (seconds elapsed since January 1, 1970)
  std::time_t now = std::time(nullptr);

  
// // Convert the current date and time to a string and output
  std::cout << std::ctime(&now) << std::endl;

    returnn 0;
}

