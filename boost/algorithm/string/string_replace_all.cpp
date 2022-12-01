/**
 * string_replace_all.cpp
 * 2020-07-01 K.OHWADA
 */


// g++ replace_all.cpp  -std=c++11 `pkg-config --cflags --libs boost` 

// replace all
// reference : https://boostjp.github.io/tips/string_algo.html#replace-all

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>


using namespace std;


/**
 * main
 */
int main(void)
{

    const string str = "Hello Jane, Hello World";
    const string search = "Hello";
    const string substitute = "Goodbye";

    cout << str << endl;

    // version that returns a copy
    {
        const std::string result = boost::algorithm::replace_all_copy(str,  search, substitute );
        cout << result << endl;
    }

    // version that makes destructive changes
    {
        string str1 = str;
        boost::algorithm::replace_all( str1,  search, substitute );
        cout << str1 << endl;
    }

    return EXIT_SUCCESS;
}


// Hello Jane, Hello World
// Goodbye Jane, Goodbye World
// Goodbye Jane, Goodbye World


