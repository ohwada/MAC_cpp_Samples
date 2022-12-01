/**
 * trim.cpp
 * 2022-06-01 K.OHWADA
 */

// remove leading and trailing spaces
// https://boostjp.github.io/tips/string_algo.html#trim

#include <iostream>
#include <string>
#include <boost/algorithm/string/trim.hpp>

using namespace std;


/**
 * main
 */
int main()
{

// version with breaking changes
    {
        string s1 = "  abc   ";
        cout << "s1 |" << s1 << '|' << endl;
        boost::algorithm::trim(s1);
        cout << "trim [" << s1 << ']' << endl;
    }


// version that returns a copy
    {
        const string s2 = "  abc   ";
        cout << "s2 |" << s2 << '|' << endl;
        const string result = boost::algorithm::trim_copy(s2);
        cout << "trim [" << result << ']' << endl;
    }

    return 0;
}

// s1 |  abc   |
// trim [abc]
// s2 |  abc   |
// trim [abc]
