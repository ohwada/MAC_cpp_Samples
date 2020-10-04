/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// join string  with hyphen(-)
// and split
// reference : https://abseil.io/docs/cpp/quickstart-cmake

#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_join.h"
// #include "absl/strings/str_split.h"

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

    const string HYPHEN = "-";

    vector<string> vec1 = {"foo", "bar", "baz"};

    cout << "strings: " ;
    dumpVector(vec1);

    string str = absl::StrJoin(vec1, HYPHEN);

    cout << "Joined with hyphen(-) : " << str << endl;

    // vector<string> vec2 = absl::StrSplit(str, HYPHEN);

    //cout << "splited strings: " ;
    //dumpVector(vec2);

    return 0;
}
