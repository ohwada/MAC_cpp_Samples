/**
 *  logic_error.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ logic_error.cpp
 // reference : https://cpprefjp.github.io/reference/stdexcept.html
#include <stdexcept>
#include <iostream>
#include <cstdlib>


/**
 *  f
 */
void f()
{
  // throw an exception
  throw std::logic_error("an exception occurred");
}


/**
 *  main
 */
int main()
{
  try {
    f();
  } 
catch (const std::logic_error& e) {
// an exception occurred！
    std::cout << e.what() << std::endl;
    std::exit(1);
  }

    return 0;
}

// an exception occurred

