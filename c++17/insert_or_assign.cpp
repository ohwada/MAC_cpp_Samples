/**
 * insert_or_assign.cpp
 * 2022-06-01 K.OHWADA
 */


// g++ insert_or_assign.cpp -std=c++17
// reference : https://qiita.com/Reputeless/items/db7dda0096f3ae91d450

#include <iostream>
#include <unordered_map>
#include <string>


/**
 * main
 */
int main()
{
    std::cout << std::boolalpha;

    std::unordered_map<std::string, int> m;

// true because insert
    std::cout << m.insert_or_assign("aaa", 5).second <<  std::endl;

// false because it is an assignment
    std::cout << m.insert_or_assign("aaa", 10).second <<  std::endl; 

    std::cout << m["aaa"] << std::endl;

    return 0;
}


// true
// false
// 10


