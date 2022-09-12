/**
 * hypot.cpp
 * 2022-06-01 K.OHWADA
 */


// g++ hypot.cpp -std=c++17 
// reference : https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <cmath>


/**
 * main
 */
int main()
{
    std::cout << std::hypot(0.0, 5.0, 0.0) << std::endl;
    std::cout << std::hypot(1.0, 1.0, 1.0) << std::endl;
    std::cout << std::hypot(2.0, 3.0, 5.0) << std::endl;

	return 0;
}


// 5
// 1.73205
// 6.16441


