/**
 *  make_unique.cpp
 * 2022-06-01 K.OHWADA
 */

/ g++ make_unique.cpp -std=c++14
// reference : https://cpprefjp.github.io/reference/memory/make_unique.html

#include <iostream>
#include <memory>
#include <utility>


/**
 *  main
 */
int main()
{
  // (1)
  // Takes a constructor argument of type T and constructs a unique_ptr object.
// here to construct a unique_ptr object of type std::pair<First, Second>
  // We are passing First type and Second type arguments.
    std::unique_ptr<std::pair<int, int>> p1 = std::make_unique<std::pair<int, int>>(3, 1);
  std::cout << p1->first << ':' << p1->second << std::endl;

  // (2)
// Construct a unique_ptr<T[]> object given the number of elements of type T[].
  // Here we are constructing an int type dynamic array with 3 elements.
  std::unique_ptr<int[]> p2 = std::make_unique<int[]>(3);
  p2[0] = 1;
  p2[1] = 2;
  p2[3] = 3;

return 0;
}

// 3:1

