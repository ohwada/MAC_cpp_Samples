/**
 *  join.cpp
 * 2022-06-01 K.OHWADA
 */

// join.cpp
// Stringify the container by specifying the delimiter
// https://boostjp.github.io/tips/string_algo.html

#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string/join.hpp>

using namespace std;



/**
 *  main
 */
int main()
{
    const vector<string> v = {"a", "b", "c"};

    for(auto x: v){
        cout << x << " ";
    }
    cout << endl;

// make it a comma separated string
    const string s = boost::algorithm::join(v, ",");
    cout << s << endl;

    return 0;
}

// a b c 
// a,b,c
