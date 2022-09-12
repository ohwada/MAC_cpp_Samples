/**
 * optional.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ optional.cpp -std=c++17
// https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <optional>


 /**
 * main
 */
int main()
{
    std::cout << std::boolalpha;

// invalid value by default
    std::optional<int> oi;

// You can also give a valid value
    //std::optional<int> oi = 100;

    if (oi)
    {   
// Not executed
        std::cout << oi.value() << std::endl;
    }

    std::cout << (oi == 200) << std::endl; // false

// set a valid value
    oi = 200;

    if (oi)
    {   
// executed
        std::cout << oi.value() << std::endl; // 200
    }

    std::cout << (oi == 200) << std::endl; // true

// if oi is invalid, return the value of the argument
    std::cout << oi.value_or(999) << std::endl; // 200

// set an invalid value
    oi = std::nullopt;

    if (oi)
    { 
// Not executed
        std::cout << oi.value() << std::endl;
    }

// if oi is invalid, return the value of the argument
    std::cout << oi.value_or(999) << std::endl; // 999

    return 0;
}


// false
// 200
// true
// 200
// 999

