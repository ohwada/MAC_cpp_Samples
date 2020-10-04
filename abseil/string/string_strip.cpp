/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// strip prefix or sufix in string


#include <iostream>
#include <string>
#include "absl/strings/strip.h"

using namespace std;


/**
 * main
 */
int main(void) 
{

    string input("abcdef");

    absl::string_view prefix("abc");
    absl::string_view out1 = absl::StripPrefix(input, prefix);

    absl::string_view sufix("def");
    absl::string_view out2 = absl::StripSuffix(input, sufix);

    cout << "StripPrefix: " << prefix << " from " << input << " -> " << out1 << endl;
    cout << "StripSufix: " << sufix << " from " << input << " -> " << out2 << endl;

    return 0;
}


// StripPrefix: abc from abcdef -> def
// StripSufix: def from abcdef -> abc

