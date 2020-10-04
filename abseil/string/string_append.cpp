/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// append string
// reference : https://abseil.io/docs/cpp/guides/strings

#include <iostream>
#include <string>
#include "absl/strings/str_cat.h"

using namespace std;


/**
 * main
 */
int main(void) 
{

// Inefficient code
    std::string s1 = "A string";
    std::string another1 = " and another string";
    s1 += " and some other string" + another1;

// Efficient code
    std::string s2 = "A string";
    std::string another2 = " and another string";
    absl::StrAppend(&s2, " and some other string", another2);

    cout << "+= : " << s1 << endl;
    cout << "StrAppend: " << s2 << endl;

    return 0;
}


// += : A string and some other string and another string
// StrAppend: A string and some other string and another string

