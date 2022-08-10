/**
 * string_array.cpp
 * 2020-07-01 K.OHWADA
 */

// g++ string_array.cpp -std=c++11

#include <iostream>
#include <string>
#include <vector>


/**
 * dump
 */
void dump(std::vector<std::string> vec) 
{
    for (auto v: vec) {
      std::cout << v << std::endl;
    } // for
}


/**
 * main
 */
int main(void) 
{
    std::vector<std::string> vec{ "Sierra", "Mojave", "Catalina" };

    dump(vec); 

    return 0;
}


// Sierra 
// Mojave 
// Catalina 


