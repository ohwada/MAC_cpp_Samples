/**
 *   equal.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  equal.cpp -std=c++14
// reference  https://cpprefjp.github.io/reference/algorithm/equal.html

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <iterator>


/**
 *   main
 */
int main() 
{
  std::vector<int>   v1  = { 1, 2, 3, 4, 3, 2 };
  std::array<int, 6> v2 = { 1, 2, 3, 4, 2, 1 };

  // check if the contents of the container are the same
  bool result = std::equal(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2));

  std::cout << std::boolalpha << result << std::endl;

// allow an error of x±1
  bool result2 = std::equal(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2),
                            [](int x, int y) { return x - 1 <= y && y <= x + 1; });

  std::cout << std::boolalpha << result2 << std::endl;

    return 0;
}

// false
// true
