/**
 * boyer_moore.cpp
 * 2022-06-01 K.OHWADA
 */

// g++-11 boyer_moore.cpp -std=c++17 
// reference : https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <string>
#include <algorithm>


/**
 * main
 */
int main()
{
    const std::string in = "ATGGTTGGTTCGCTAAACTGCATCGTCGCTGTGTCCCAGAA";
    const std::string pattern = "TGTGTCCCAG";

     std::boyer_moore_searcher searcher(pattern.begin(), pattern.end());    
    
    const auto it = std::search(in.begin(), in.end(), searcher);



    if (it != in.end()) 
    {
// found
        std::cout << std::distance(in.begin(), it) << std::endl; // 29
    }
    else
    {
        std::cout << "not found" << std::endl;;
    }
}

// 29
