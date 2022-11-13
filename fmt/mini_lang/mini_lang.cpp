/**
 * mini_lang.cpp
 * 2022-06-01 K.OHWADA
 */

// Format Specification Mini-Language
// https://fmt.dev/latest/syntax.html#formatspec


#include <iostream>
#include <fmt/core.h>

using namespace std;


/**
 * main
 */
int main()
{
    string FORMAT1("{:02d}");
    string FORMAT2("{:1.2f}");
    string FORMAT3("|{:>5}|");

    int val1= 1;
    float val2 = 3.1415;
    string s("abc");

    cout << "int: " << FORMAT1 << " ; " << val1  << endl;
    fmt::print(FORMAT1, val1);
    cout << endl;

    cout << "float: " << FORMAT2<< " ; "  << val2 << endl;
    fmt::print(FORMAT2, val2);
    cout << endl;

    cout << "string: " << FORMAT3 << " ; |"<< s << "|" << endl;
    fmt::print(FORMAT3, s);
    cout << endl;

    return 0;
}

