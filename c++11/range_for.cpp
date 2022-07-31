 /**
 *  range_for.cpp
 * 2022-06-01 K.OHWADA
 */

//  g++ range_for.cpp -o rang_for -std=c++11

#include<iostream>
#include<vector>


 /**
 *  main
 */
int main()
{
 // List-initialization
	std::vector<int> vec{ 0, 1, 2, 3 };

// Range-based for loop
// keywords: auto
	for(auto v: vec) 
	{
		std::cout << v << std::endl;
	}

	return 0;
}


// 0
// 1
// 2
// 3


