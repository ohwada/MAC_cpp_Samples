/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// test for string_view container
// reference : https://abseil.io/docs/cpp/guides/strings

#include <iostream>
#include <string>
#include "absl/strings/string_view.h"

using namespace std;


// If an API declare a string literal as const char ...
const char kGreeting[] = "hello";

// API users could access this string data for reading using a string_view.
absl::string_view GetGreeting() {
    return kGreeting; 
}


/**
 * main
 */
int main(void) 
{

    cout << GetGreeting() << endl;

    return 0;
}

// hello
