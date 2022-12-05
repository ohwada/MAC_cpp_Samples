/**
 *   numbers.cpp
 * 2022-06-01 K.OHWADA
 */

// https://qiita.com/Chippppp/items/620d2e5229f5c7e93f0c
// https://cpprefjp.github.io/reference/numbers.html

#include <iostream>
#include <numbers>


/**
 *   main
 */
int main() 
{

// math constant of type double
    std::cout << "pi: " << std::numbers::pi <<  std::endl;
    // 3.14159

    std::cout << "e: " << std::numbers::e << std::endl;
    // 2.71828

// You can also specify the type
    std::cout << "phi: " << std::numbers::phi_v<long double> << std::endl;
    // 1.61803

    return 0;
}


