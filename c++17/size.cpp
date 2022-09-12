/**
 *  size.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ size.cpp -std=c++17
// reference : https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <vector>


/**
 * main
 */
int main()
{
    std::cout << std::boolalpha;

    int ar[10];
    std::vector<int> v;

    std::cout << std::size(ar) << std::endl; // 10
    std::cout << std::size(v) << std::endl; // 0

    std::cout << std::empty(ar) << std::endl; // false
    std::cout << std::empty(v) << std::endl; // true

    return 0;
}


// 10
// 0
// false
//true


