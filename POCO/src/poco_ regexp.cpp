/**
 * poco_regexp.cpp
 * 2022-06-01 K.OHWADA
 */

// Poco/RegularExpression 
// https://docs.pocoproject.org/current/Poco.RegularExpression.html

// reference : https://www.qoosky.io/techs/8e92d3d34a

#include <iostream>
#include <Poco/RegularExpression.h>

/**
 * main
 */
int main() 
{
    Poco::RegularExpression regexp("^[a-zA-Z]+");

    std::string buf;
    regexp.extract("ABC123", buf);
    std::cout << buf << std::endl; //=> ABC

    return 0;
}
