/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// substitute. string
// reference : https://abseil.io/docs/cpp/guides/strings

#include <iostream>
#include <string>
#include "absl/strings/substitute.h"

using namespace std;



/**
 * main
 */
int main(void) 
{

    std::string s1 = 
    absl::Substitute("$1 purchased $0 $2. Thanks $1!", 
    5, "Bob", "Apples");
// Produces the string "Bob purchased 5 Apples. Thanks Bob!"


    std::string s2 = "Hi. ";
    absl::SubstituteAndAppend(&s2, 
    "My name is $0 and I am $1 years old.", 
    "Bob", 5);
// Produces the string "Hi. My name is Bob and I am 5 years old."

    cout << "Substitute: " << s1 << endl;
    cout << "SubstituteAndAppend: " << s2 << endl;

    return 0;
}


// Substitute: Bob purchased 5 Apples. Thanks Bob!
// SubstituteAndAppend: Hi. My name is Bob and I am 5 years old.

