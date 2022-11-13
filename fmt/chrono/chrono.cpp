/**
 *  chrono.cpp
 * 2022-06-01 K.OHWADA
 */

// Print chrono durations 

#include <iostream>
#include <fmt/chrono.h>

// c++14
using namespace std;
using namespace std::literals::chrono_literals;


/**
 *  main
 */
int main() 
{
// Print chrono durations 
    string FORMAT1("{} {}");
    cout<< "Default format: " <<  FORMAT1 << endl;
    fmt::print( FORMAT1, 42s, 100ms);
    cout << endl;

    string FORMAT2("{:%H:%M:%S}");
    cout<< "strftime-like format: " <<  FORMAT2 << endl;
    fmt::print(FORMAT2, (3h + 15min + 30s) );
    cout << endl;

    return 0;
}

