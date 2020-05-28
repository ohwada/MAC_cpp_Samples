/**
 * boost Samples
 * 2020-03-01 K.OHWADA
 */

// split string
// reference : https://www.gesource.jp/weblog/?p=4531

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

using namespace std;

/**
 * main
 */
int main(int argc, char** argv)
{

// sample1 : separate with ','
    string str1 = "abc,def,ghi,jkl";
    list<string> results1;
    boost::split(results1, str1, boost::is_any_of(","));

    cout << "split with ',' " << endl;
    cout << str1 << endl;
    BOOST_FOREACH(string p1, results1) {
        cout << p1 << endl;
    }
    cout  << endl;

// sample2 : separated by white space
    string str2 = "More Effective C++";

    cout << "split by white space" << endl;
    list<string> results2;
    boost::split(results2, str2, boost::is_space());


    cout << str2 << endl;
    BOOST_FOREACH(string p2, results2) {
        cout << p2 << endl;
    }
    cout  << endl;

// sample3
// separate by multiple slashe, space, and colon
    string str3 = "2011/02/09 20:19:33";
    list<string> results3;
    boost::split(results3, str3, boost::is_any_of("/ :"));

    cout << "split by slash, space, colon" << endl;
    cout << str3 << endl;
    BOOST_FOREACH(string p3, results3) {
        cout << p3 << endl;
    }
    cout  << endl;

    return EXIT_SUCCESS;
}
