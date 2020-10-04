/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// containg substring in string
// reference : https://abseil.io/docs/cpp/guides/strings

#include <iostream>
#include <string>


#include "absl/strings/match.h"

using namespace std;


/**
 * main
 */
int main(void) 
{

    string msg = "foo bar baz";
    string str = "bar";
    if (absl::StrContains(msg, str)) {
        cout << "'" << msg << "' contains " << str << endl;
    }

    return 0;
}


// 'foo bar baz' contains bar

