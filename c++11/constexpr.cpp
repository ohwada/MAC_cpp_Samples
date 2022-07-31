/**
 *  constexpr.cpp 
 * 2022-06-01 K.OHWADA
 */

// g++ constexpr11.cpp  -std=c++11
// reference : https://qiita.com/saltheads/items/dd65935878a0901fe9e7

#include <iostream>


/**
 *  twice
 */
constexpr int twice(const int n) {
  return n * 2;
}


/**
 *  main
 */
int main()
{
constexpr int ten = 10;
constexpr int ten2 = twice(ten);

std::cout << "ten: " << ten << std::endl;
std::cout <<  "ten2: " << ten2 << std::endl;

 // complie error
// constexpr int tenx = twice(static_cast<int>(rand() % 10)); 

	return 0;
}

