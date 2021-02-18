/**
 * c++ string sample
 * 2020-03-01 K.OHWADA
 */

// test for string_replace.hpp

#include <iostream>
#include "string_replace.hpp"

using namespace std;


/**
 *  main
 */
int main(void)
{

    string sample = "hello world goodby world";
    string s1 = "world";
    string s2 = "japan";

    cout << "original:"<< endl;
    cout << sample << endl;
    cout << s1 << " -> " << s2 << endl;

    string result1;
    replaceString(sample, s1,  s2,  result1);


    cout << "replaced:"<< endl;
    cout << result1 << endl;

    cout << endl;
    cout << "try: " << s2 << " -> " << s1 << endl;

    string result2;
    replaceString(sample, s2,  s1, result2);

    if ( result2.empty() ) {
        cout << "not found:" << s2 << endl;
    }

    cout << endl;
    cout << "remove: " << s1 << endl;

    string result3;
    replaceString(sample, s1,  "",  result3);

     cout << "removeed:" << endl;
    cout << result3 << endl;

    return 0;
}


// original:
// hello world goodby world
// world -> japan
// replaced:
// hello japan goodby world
// try: japan -> world
// not found:japan
// remove: world
// removeed:
// hello  goodby world

