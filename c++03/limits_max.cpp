/**
 *  limits_max.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ limits_max.cpp
// reference : https://cpprefjp.github.io/reference/limits/numeric_limits/max.html

#include <iostream>
#include <limits>


/**
 *  main
 */
int main()
{
  const int i = std::numeric_limits<int>::max();
  const double d = std::numeric_limits<double>::max();

  std::cout << i << std::endl;
  std::cout << d << std::endl;
}


// 2147483647
// 1.79769e+308

