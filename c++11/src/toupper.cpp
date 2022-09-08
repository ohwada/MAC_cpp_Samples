/**
 *  toupper.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ toupper.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/locale/toupper.html

#include <locale>
#include <iostream>


/**
 *  main
 */
int main()
{
  std::locale l = std::locale::classic();

  std::cout << std::toupper('a', l) << std::endl;

	return 0;
}

// A

