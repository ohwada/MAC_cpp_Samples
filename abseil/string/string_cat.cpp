/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// catenate string
// reference : https://abseil.io/docs/cpp/guides/strings

#include <iostream>
#include <string>
#include "absl/strings/str_cat.h"

using namespace std;


/**
 * MyFunction
 */
absl::string_view MyFunction(void)
{
    absl::string_view sv = " MyFunction";
    return sv;
}


/**
 * main
 */
int main(void) 
{

// absl::StrCat() can merge an arbitrary number of strings
    std::string s1;
    s1 = absl::StrCat("A string ", " another string", " yet another string");

// StrCat() also can mix types, including std::string, string_view, literals,
// and more.
    std::string s3;
    std::string s2 = "Foo";
    absl::string_view sv1 = MyFunction();
    s3 = absl::StrCat(s2, sv1, " a literal");

    cout << "StrCat: " << s1 << endl;
    cout << "mix types: " << s3 << endl;

    return 0;
}


// StrCat: A string  another string yet another string
// mix types: Foo MyFunction a literal
