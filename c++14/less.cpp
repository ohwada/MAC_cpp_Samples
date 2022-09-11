/**
 *  less.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ less.cpp
// https://cpprefjp.github.io/reference/functional/less.html
#include <iostream>
#include <functional>


/**
 *  main
 */
int main()
{
  std::cout << std::boolalpha << std::less<>()(2, 3) << std::endl;
}

// true
