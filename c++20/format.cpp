/**
 *   format.cpp
 * 2022-06-01 K.OHWADA
 */

// https://qiita.com/Chippppp/items/620d2e5229f5c7e93f0c
// https://cpprefjp.github.io/reference/format/format.html


#include <iostream>

// TODO:
// fatal error: 'format' file not found
#include <format>


/**
 * main
 */
int main() 
{
    int a = 1, b = 2;
    std::cout << std::format("a, b = {}, {}\n", a, b);
    // a, b = 1, 2

// specify the order
    std::cout << std::format("b, a = {1}, {0}\n", a, b);
    // b, a = 2, 1

    return 0;
}

