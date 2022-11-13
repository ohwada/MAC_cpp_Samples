/**
 * positional.cpp
 * 2022-06-01 K.OHWADA
 */

// The format API also supports positional arguments
// https://fmt.dev/latest/index.html

#include <iostream>
#include <fmt/core.h>

using namespace std;


/**
 * main
 */
int main()
{
    string FORMAT("I'd rather be {1} than {0}");
    cout << FORMAT << endl;

    fmt::print("I'd rather be {1} than {0}. \n", "right", "happy");
    cout << endl;

    return 0;
}

