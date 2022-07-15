/**
 * poco_log.cpp
 * 2022-06-01 K.OHWADA
 */

// cat, trim, oUpper
// reference : https://codezine.jp/article/detail/2098?p=3

#include <iostream>
#include "Poco/String.h"

/**
 * main
 */
int main()
{
std::string str1 = "  The above copyright notice\t";
std::string str2 = " shall be included";

// simple string concatenation
std::cout << Poco::cat( str1, str2 ) << std::endl;             

std::cout << Poco::cat( Poco::trimRight( str1 ), str2 ) 
                                          << std::endl; 
std::cout << Poco::cat( Poco::trimInPlace( str1 ), str2 ) 
                                          << std::endl; 
std::cout << Poco::cat( str1, str2 ) << std::endl; 
std::cout << Poco::cat( str1, Poco::toUpper( str2 ) ) 
                                          << std::endl;
std::cout << Poco::icompare( str2, Poco::toUpper( str2 ) ) 
                                          << std::endl; 


// Convert "c" to "1" and "o" to "2"
std::cout << Poco::translate( str1, std::string("co"), 
                             std::string("12") ) << std::endl;

// simply replace "co" with "12"
std::cout << Poco::replace( str1, std::string("co"), 
                             std::string("12") ) << std::endl;
return 0;
}
