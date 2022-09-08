/**
 *   move.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  move.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/algorithm/move.html

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <memory>



/**
 *   main
 */
int main() 
{
  std::vector<std::unique_ptr<int>> v1;
std::vector<std::unique_ptr<int>> v2;

  for (int i = 0; i < 5; i++){
    v1.emplace_back(new int(i));
}


std::cout << "v1: ";
  std::for_each(v1.begin(), v1.end(),
    [](const std::unique_ptr<int>& v) { std::cout << *v << ", "; });
std::cout << std::endl;


  // move each element of v1 to v2
  std::move(v1.begin(), v1.end(), std::back_inserter(v2));


std::cout << "v2: ";
  std::for_each(v2.begin(), v2.end(),
    [](const std::unique_ptr<int>& v) { std::cout << *v << ", "; });
std::cout << std::endl;


 std::cout << "v1: ";
for(int i=0; i<v1.size(); i++){
    std::cout << v1[1] << ", ";
}
std::cout << std::endl;


    return 0;
}

// v1: 0, 1, 2, 3, 4, 
// v2: 0, 1, 2, 3, 4, 
// v1: 0x0, 0x0, 0x0, 0x0, 0x0, 

