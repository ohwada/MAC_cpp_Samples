/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// split string  with comma(,)
// reference : https://abseil.io/docs/cpp/guides/strings

#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"

using namespace std;


/**
 * dumpVector
 */
void dumpVector(vector<string> vec)
{
    for(string x: vec){
        cout << x << ", ";
    }
    cout << endl;
}


/**
 * main
 */
int main(void) 
{

    const string COMMA = ",";

    string str = "a,b,c";

    cout << "string: " << str << endl;

    vector<string> vec = absl::StrSplit(str, COMMA);

    cout << "splited strings: " ;
    dumpVector(vec);

    return 0;
}
