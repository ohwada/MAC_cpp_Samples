/**
 *  return_value.cpp
 * 2022-06-01 K.OHWADA
 */

// lambda can return a return value.
// since lambda is a function object
// https://cpplover.blogspot.com/2009/11/lambda.html

#include <iostream>

using namespace std;


/**
 * main
 */
int main()
{

// The return value will be guessed even if you don't write it explicitly
    auto a = []{ return 123 ; }() ;

// If you write the return value explicitly.
// Type conversion from double to float.
    auto b = []() -> float { return 3.14 ; }() ; 

    cout << a << endl;
    cout << b << endl;

    return 0;
}

