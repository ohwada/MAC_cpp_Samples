/**
 *   emplace_back..cpp
 * 2022-06-01 K.OHWADA
 */

// g++  emplace_back..cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/vector/vector/emplace_back.html

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>


/**
 *  main
 */
int main()
{
  std::vector<std::pair<int, std::string>> v;

  v.emplace_back(3, std::string("hello"));
  v.push_back(std::make_pair(1, std::string("world")));

  std::for_each(v.begin(), v.end(), [](decltype(v)::const_reference x) {
    std::cout << x.first << ',' << x.second << std::endl;
  });

    return 0;
}

// 3,hello
// 1,world
