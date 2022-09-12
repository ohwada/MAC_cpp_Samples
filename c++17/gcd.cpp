/**
 *  gcd.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ gcd.cpp -std=c++17
// reference :https://qiita.com/Reputeless/items/db7dda0096f3ae91d450'

#include <iostream>
#include <numeric>


/**
 *  main
 */
int main()
{

    std::cout << std::gcd(554433221100LL, 12345) << std::endl; // 15

    std::cout << std::lcm(554433221100LL, 12345) << std::endl; // 456298540965300
}

// 15
// 456298540965300


