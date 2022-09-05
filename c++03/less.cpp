/**
 *  less.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ less.cpp
// reference : https://cpprefjp.github.io/reference/functional/less.html
#include <iostream>
#include <functional>


/**
 *  main
 */
int main()
{
  std::cout << std::boolalpha << std::less<int>()(2, 3) << std::endl;
}

// true
