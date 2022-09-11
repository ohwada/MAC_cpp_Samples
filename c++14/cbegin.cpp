/**
 * cbegin.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ cbegin.cpp -std=c++14
// reference : https://cpprefjp.github.io/reference/iterator/cbegin.html 

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


/**
 * main
 */
int main()
{
  std::vector<int> v = {1, 2, 3};

  decltype(v)::const_iterator first = std::cbegin(v);
  decltype(v)::const_iterator last = std::cend(v);

  std::for_each(first, last, [](const int& x) {
    std::cout << x << std::endl;
  });

    return 0;
}


// 1
// 2
// 3

