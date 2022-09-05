/**
 *  array.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ array.cpp
// reference : https://cpprefjp.github.io/reference/array/array.html
#include <iostream>
#include <array>
#include <algorithm>


/**
 *  disp
 */
void disp(int x) 
{
  std::cout << x << std::endl;
}


/**
 *  main
 */
int main()
{
// define a 3-element int array and initialize it with an initializer list
  std::array<int, 3> ar = {3, 1, 4};

  // get number of elements by size() member function
  for (std::size_t i = 0; i < ar.size(); ++i) 
{
// random access to arbitrary elements with operator[]
    ++ar[i];
  }

  // traversing an element with a terminator
  std::for_each(ar.begin(), ar.end(), disp);


    return 0;
}

// 4
// 2
// 5
