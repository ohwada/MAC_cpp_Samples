/**
 * boost Samples
 * 2020-03-01 K.OHWADA
 */

// example : to_upper, trim, to_lower_copy
// reference : https://www.boost.org/doc/libs/1_57_0/doc/html/string_algo/usage.html

#include <boost/algorithm/string.hpp>

#include <string> 
#include<iostream>

using namespace std;
using namespace boost;
    

/**
 * main
 */
int main(int argc, char** argv)
{

    string str1(" hello world! ");
    cout << "original : " << str1 << endl;

    to_upper(str1);  // str1 == " HELLO WORLD! "
    cout << "to_upper : " << str1 << endl;

    trim(str1);      // str1 == "HELLO WORLD!"
    cout << "trim : " << str1 << endl;

    string str2 = ireplace_first_copy(
             str1, "hello", "GOODBYE");
    cout << "ireplace_first_copy : " << str2 << endl;

    string str3 =
       to_lower_copy(str2); // str3 == "goodbye world!"


    cout << "to_lower_copy : " << str3 << endl;

    return EXIT_SUCCESS;
}
