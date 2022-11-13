/**
 *  string.cpp
 * 2022-06-01 K.OHWADA
 */

// Format a string
// https://github.com/fmtlib/fmt

#include <iostream>
#include <fmt/core.h>

using namespace std;


/**
 *  main
 */
int main() 
{
// Format a string
    string FORMAT1("The answer is {}.");
    cout << FORMAT1 << endl;
    std::string s1 = fmt::format(FORMAT1, 42);
    cout << s1 << endl;


// Format a string using positional arguments
    string FORMAT2("I'd rather be {1} than {0}.");
    cout << FORMAT2 << endl;
std::string s2 = fmt::format( FORMAT2, "right", "happy");
    cout << s2 << endl;
// s == "I'd rather be happy than right."

    return 0;
}

