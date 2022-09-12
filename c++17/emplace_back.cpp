/**
 *   emplace_back.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ emplace_back.cpp -std=c++17
// reference : https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <vector>
#include <utility>


/**
 * main
 */
int main()
{
    std::vector<std::pair<int, int> > v;

    // v.emplace_back(11, 33)
    // const auto p = v.back();


//can do in  C++17 
    const auto p = v.emplace_back(11, 33);
 
    std::cout << p.first << std::endl; // 11

    return 0;
}

// 11