/**
 * tuple.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ tuple.cpp -std=c++17
// https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <tuple>


/**
 * GetTuple
 */
std::tuple<int, int, std::string> GetTuple()
{
    // return std::make_tuple(20, 40, "ABC");
// correct in C++17
    return{ 20, 40, "ABC" };
}


/**
 * main
 */
int main()
{
// structured binding
    auto [a, b, c] = GetTuple();

    std::cout << a << ',' << b << ',' << c << std::endl;

    return 0;
}


// 20,40,ABC

