/**
 * boost Samples
 * 2020-03-01 K.OHWADA
 */

// split string
// reference : https://www.boost.org/doc/libs/1_57_0/doc/html/string_algo/usage.html

// g++ test_split.cpp -std=c++11  -I/usr/local/Cellar/boost/1.73.0/include/ -L/usr/local/Cellar/boost/1.73.0/lib -lboost_system


#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>


using namespace std;


/**
 * dump
 */
void dump(vector<string> vec)
{
    for(auto v: vec) {
        cout << v << endl;
    }
    cout << endl;
}


/**
 * main
 */
int main(void)
{

  // sample1 : separate with ','
    string str1 = "abc,def,ghi,jkl";
    vector<string> results1;

    boost::split(results1, str1, boost::is_any_of(","));

    cout << "split with ',' " << endl;
    cout << str1 << endl;
    
    dump(results1);

// sample2 : separated by white space
 string str2("hello goodbye boost split");

    cout << "split by white space" << endl;
    vector<string> results2;

    boost::split(results2, str2, boost::is_space());


    cout << str2 << endl;

    dump(results2);

// sample3
// separate by multiple slashe, space, and colon
    string str3 = "2011/02/09 20:19:33";
    vector<string> results3;

    boost::split(results3, str3, boost::is_any_of("/ :"));

    cout << "split by slash, space, colon" << endl;
    cout << str3 << endl;

    dump(results3);

// split with ',' 
// abc,def,ghi,jkl
// abc
// def
// ghi
// jkl
//
// split by white space
// hello goodbye boost split
// hello
// goodbye
// boost
// split
//
// split by slash, space, colon
// 2011/02/09 20:19:33
// 2011
// 02
// 09
// 20
// 19
// 33

    return EXIT_SUCCESS;
}
