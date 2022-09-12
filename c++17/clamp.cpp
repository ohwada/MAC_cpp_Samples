/**
 *  clamp.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ clamp.cpp -o clamp -std=c++17 

// https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <algorithm>


/**
 *  main
 */
int main()
{
// keep the value between 0 and 100
    std::cout << std::clamp(50, 0, 100) << std::endl;
    std::cout << std::clamp(-50, 0, 100) << std::endl;
    std::cout << std::clamp(150, 0, 100) << std::endl;
	return 0;
}


// 50
// 0
// 100
