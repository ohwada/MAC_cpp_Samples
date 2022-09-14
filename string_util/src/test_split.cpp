/*
 * test_split.cpp
 * 2022-06-01 K.OHWADA 
*/

#include <iostream>
#include "split.hpp"

using namespace std;


/*
 * main
*/
int main()
{
    string text("The quick brown fox jumps over the lazy dog");
    char delim = ' '; 

    cout << text << endl;

    auto data = split(text, delim);

    for(auto str: data)
    {
        cout << str << endl;
    }

    return 0;
}


// The
// quick
// brown
// fox
// jumps
// over
// the
// lazy
// dog


