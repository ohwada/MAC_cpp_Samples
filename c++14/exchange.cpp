/**
 *  exchange.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ exchange.cpp -std=c++14
// reference : https://cpprefjp.github.io/reference/utility/exchange.html

#include <iostream>
#include <utility>


/**
 *  main
 */
int main()
{
  int state = 1;
  int before = std::exchange(state, 2);

  std::cout << "state : " << state << std::endl;
  std::cout << "before : " << before << std::endl;
}

// state : 2
// before : 1
