/**
 *   map_contains.cpp
 * 2022-06-01 K.OHWADA
 */

//https://qiita.com/Chippppp/items/620d2e5229f5c7e93f0c
// https://cpprefjp.github.io/reference/map/map/contains.html

#include <iostream>
#include <map>
#include <unordered_set>


/**
 *   main
 */
int main() 
{
    std::map<int, int> a{{1, 2}, {1, 3}, {3, 4}};
    std::unordered_multiset<int> b{1, 2, 3};

    std::cout << std::boolalpha;
    std::cout << a.contains(1) << '\n';
    std::cout << b.contains(4) << '\n';
    // true
    // false

    return 0;
}



