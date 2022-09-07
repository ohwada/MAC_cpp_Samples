/**
 * trim.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include "trim.hpp"
 

 /**
 * main
 */
int main()
{
    std::string s = "\n\tHello World  \r\n";
    std::cout << "START::" << trim(s) << "::END";
 
    return 0;
}
