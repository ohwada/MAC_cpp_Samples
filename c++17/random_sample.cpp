/**
 *  random_sample.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ random_sample.cpp -std=c++17

// https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <algorithm>
#include <random>


/**
 *  main
 */
int main()
{
    const std::string in = "ABCDEFG";
    const int N = 4;
    std::string out;

// N randomly select
    std::sample(in.begin(), in.end(), std::back_inserter(out), N, std::mt19937{std::random_device{}()});
    
    std::cout << out << std::endl;
    return 0;
}

// BCEG
