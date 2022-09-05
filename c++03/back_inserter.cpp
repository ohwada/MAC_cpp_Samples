/**
 *  back_inserter.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ back_inserter.cpp
// reference : https://cpprefjp.github.io/reference/iterator/back_inserter.html

#include <iostream>
#include <vector>
#include <algorithm>


/**
 *  main
 */
int main()
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);


  std::vector<int> dest;

// copy the elements of src while adding them to dest
  dest.reserve(src.size());
  std::copy(src.begin(), src.end(), std::back_inserter(dest));

  for(int i=0; i<dest.size(); i++) 
{
    std::cout << dest[i] << std::endl;
  } // for

    return 0;
}

// 1
// 2
// 3

