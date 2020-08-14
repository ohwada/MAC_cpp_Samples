/**
 * boost Samples
 * 2020-03-01 K.OHWADA
 */

// boost examples : 
// to_upper
// to_lower_copy
// trim
// replace_first_copy
// ireplace_first_copy

// reference : https://www.boost.org/doc/libs/1_57_0/doc/html/string_algo/usage.html
// https://www.boost.org/doc/libs/1_63_0/doc/html/boost/algorithm/

// g++ test_boost_example.cpp  -I/usr/local/Cellar/boost/1.73.0/include/ -L/usr/local/Cellar/boost/1.73.0/lib -lboost_system


#include <string> 
#include<iostream>
#include <boost/algorithm/string.hpp>
#include <boost/version.hpp>

using namespace std;
using namespace boost;
    

/**
 * main
 */
int main(void)
{

    cout << "boost version: " << BOOST_LIB_VERSION << endl;

    string str1(" hello world! ");
    cout << "original : " << str1 << endl;

    string str2 = str1;
    to_upper(str2); 
    cout << "to_upper : " << str2 << endl;

    string str3 = 
       to_lower_copy(str2); 
    cout << "to_lower_copy : " << str3 << endl;

    string str4 = str1;
   cout << endl;
    cout << "original : '" << str4 << "'" << endl;
    trim(str4);  
    cout << "trim : '" << str4 << "'"<< endl;

// Replace first algorithm( case sensitive )
   cout << endl;
    cout << "original : " << str2 << endl;
    string str5 = replace_first_copy(
             str2, "hello", "GOODBYE");
    cout << "try to replace hello to GOODBYE" << endl;
    cout << "replace_first_copy : " << str5 << endl;

// Replace first algorithm ( case insensitive )
    string str6 = ireplace_first_copy(
             str2, "hello", "GOODBYE");
    cout << "ireplace_first_copy : " << str6 << endl;

 string str7 = replace_first_copy(
             str2, "HELLO", "GOODBYE");
   cout << endl;
    cout << "try to replace HELLO to GOODBYE" << endl;
    cout << "replace_first_copy : " << str7 << endl;


// boost version: 1_73
// original :  hello world! 
// to_upper :  HELLO WORLD! 
// to_lower_copy :  hello world! 
//
// original : ' hello world! '
// trim : 'hello world!'
//
// original :  HELLO WORLD! 
// try to replace hello to GOODBYE
// replace_first_copy :  HELLO WORLD! 
// ireplace_first_copy :  GOODBYE WORLD! 

// try to replace HELLO to GOODBYE
// replace_first_copy :  GOODBYE WORLD! 

    return EXIT_SUCCESS;
}
