/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// strip AsciiWhitespace in string

#include <iostream>
#include <string>
#include "absl/strings/ascii.h"

using namespace std;



/**
 * main
 */
int main(void) 
{

// StripAsciiWhitespace
    std::string s1("\tabcd\n");

    absl::string_view s2 = absl::StripAsciiWhitespace(s1); 

    cout << "StripAsciiWhitespace" << endl;
    cout << "'" << s1 <<  "'" << endl;
    cout << "'" << s2 <<  "'" << endl;


// AsciiStrToUpper
    std::string s3("abcd");

    absl::string_view s4 = absl::AsciiStrToUpper(s3);

    cout << "AsciiStrToUpper" << endl;
    cout << s3 << endl;
    cout << s4 << endl;


    return 0;
}

// StripAsciiWhitespace
// '	abcd
// '
// 'abcd'
// AsciiStrToUpper
// abcd
// ABCD
