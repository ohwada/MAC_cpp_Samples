/**
 *  iends_with.cpp
 * 2022-06-01 K.OHWADA
 */


// determine extension
// https://boostjp.github.io/tips/string_algo.html#iends-with

#include <iostream>
#include <string>
#include <boost/algorithm/string/predicate.hpp> // iends_with


/**
 *  is_file_ext
 */
bool is_file_ext(const std::string& filename, const std::string& ext)
{
    return boost::algorithm::iends_with(filename, ext);
}


using namespace std;



/**
 *  main
 */
int main()
{
    const string filename = "example.cpp";
    const string ext = "cpp";

    cout  <<  "filename: " <<  filename << endl;
    cout <<  "ext: " << ext << endl;

    const bool result = is_file_ext(filename, ext);

    cout << "result: "<< std::boolalpha << result << endl;

    return 0;
}

// result: true
