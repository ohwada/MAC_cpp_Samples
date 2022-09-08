/**
 *   random_device.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  random_device.cpp -std=c++11
// https://cpprefjp.github.io/reference/random/random_device.html

#include <iostream>
#include <random>


/**
 *   main
 */
int main()
{
  std::random_device rng;

  for (int i = 0; i < 10; ++i) 
{
// generate unpredictable random numbers
    unsigned int result = rng();

    std::cout << result << std::endl;
  } // for

    return 0;
}

// 602498380
// 1724208309

