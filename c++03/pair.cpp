/**
 *  pair.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ pair.cpp 
// reference : https://cpprefjp.github.io/reference/utility/pair.html
#include <iostream>
#include <utility>
#include <string>


/**
 *  main
 */
int main()
{
  // constructing a pair object
  std::pair<int, std::string> p = std::make_pair(1, "hello");

  // element reference
  std::cout << p.first << std::endl;
  std::cout << p.second << std::endl;

    return 0;
}

// 1
// hello


