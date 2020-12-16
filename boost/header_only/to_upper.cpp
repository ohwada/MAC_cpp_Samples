/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// to_upper
// convert lowercase letters to uppercase

// reference : https://www.boost.org/doc/libs/1_57_0/doc/html/string_algo/usage.html


#include <string> 
#include<iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

    
/**
 * main
 */
int main(void)
{

    string str1(" hello world! ");
    cout << "original : " << str1 << endl;

    string str2 = str1;
    boost::to_upper(str2); 
    cout << "to_upper : " << str2 << endl;

    return EXIT_SUCCESS;
}


// original :  hello world! 
// to_upper :  HELLO WORLD! 

