/**
 *  begin.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ begin.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/iterator/begin.html

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


/**
 *  print
 */
void print(int x)
{
  std::cout << x << " ";
}


/**
 *  maain
 */
int main()
{

// container
  {
    std::vector<int> v = {1, 2, 3};

    decltype(v)::iterator first = std::begin(v);
    decltype(v)::iterator last = std::end(v);

    std::for_each(first, last, print);
    std::cout << std::endl;
  }

// built-in array
  {
    int ar[] = {4, 5, 6};

    int* first = std::begin(ar);
    int* last = std::end(ar);

    std::for_each(first, last, print);
    std::cout << std::endl;
  }

    return 0;
}

// 1 2 3 
// 4 5 6    