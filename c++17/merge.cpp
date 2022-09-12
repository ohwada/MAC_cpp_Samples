/**
 * merge.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ merge.cpp -std=c++17
// reference : https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <unordered_set>


/**
 * main
 */
int main()
{
    std::unordered_set<int> s1 = { 10, 8, 5, 4 };
    std::unordered_set<int> s2 = { 10, 6, 4, 2 };

// extraction and merge from s2 to s1
    s1.merge(s2);

    std::cout << "s1: ";
    for (const auto& e : s1)
    {
        std::cout << e << ' ';
    }
    std::cout <<  std::endl; 

    std::cout << "\ns2: ";
    for (const auto& e : s2)
    {
// 4 and 10 are not extracted because they existed in s1
        std::cout << e << ' '; 
    }
    std::cout <<  std::endl; 

    return 0;
}

// s1: 6 2 4 8 5 10 
// s2: 4 10 

                                                                   
