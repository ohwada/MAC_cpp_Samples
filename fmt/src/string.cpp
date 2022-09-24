/**
 *  string.cpp
 * 2022-06-01 K.OHWADA
 */

// Format a string
// https://github.com/fmtlib/fmt

#include <iostream>
#include <fmt/core.h>

int main() 
{
// Format a string
    std::string s1 = fmt::format("The answer is {}.", 42);
    std::cout << s1 << std::endl;


// Format a string using positional arguments
std::string s2 = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    std::cout << s2 << std::endl;
// s == "I'd rather be happy than right."

    return 0;
}

