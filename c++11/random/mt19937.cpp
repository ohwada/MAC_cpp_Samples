/**
 *   mt19937.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ mt19937.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/random/mt19937.html

#include <iostream>
#include <random>


/**
 *  main
 */
int main()
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());

  for (int i = 0; i < 10; ++i) {
    std::uint32_t result = engine();
    std::cout << result << std::endl;
  } // for

    return 0;
}

// 2519283868
// 1821060167
