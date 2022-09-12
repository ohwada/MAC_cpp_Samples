/**
 * not_fn.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ not_fn.cpp -std=c++17 
// reference : https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <vector>


/**
 *  LessThan10
 */
bool LessThan10(int n)
{
    return n < 10;
}


/**
 * main
 */
int main()
{
    std::vector<int> v = { 3, 5, 7, 9, 11 };

    std::cout << std::count_if(v.begin(), v.end(), LessThan10) << std::endl; // 4

    std::cout << std::count_if(v.begin(), v.end(), std::not_fn(LessThan10)) << std::endl; // 1
}


// 4
// 1

