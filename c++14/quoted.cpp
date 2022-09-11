/**
 * quoted.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ quoted.cpp -std=c++14
// reference : https://cpprefjp.github.io/reference/iomanip/quoted.html

#include <iostream>
#include <sstream>
#include <string_view>
#include <iomanip>


/**
 * main
 */
int main()
{
  // (1) : Enclose a string in double quotes and output
  {
    std::stringstream ss;
    ss << std::quoted("hello");
    std::cout << "(1) : " << ss.str() << std::endl;
  }

  // (2) : Output a std::basic_string string enclosed in single quotes
  {
    std::string s = "hello";

    std::stringstream ss;
    ss << std::quoted(s, '\'');
    std::cout << "(2) : " << ss.str() << std::endl;
  }

  // (3) : std::basic_string_view Output the string enclosed in double quotes
  {
    std::string_view sv = "hello";

    std::stringstream ss;
    ss << std::quoted(sv);
    std::cout << "(3) : " << ss.str() << std::endl;
  }

  // (4) : Extract string enclosed in double quotes
    std::stringstream ss;
    ss << "\"hello\"";

    std::string input;
    ss >> std::quoted(input);
    std::cout << "(4) : " << input << std::endl;
  }

  // (4) : Strings not enclosed in double quotes can also be read
  {
    std::stringstream ss;
    ss << "hello";

    std::string input;
    ss >> std::quoted(input);
    std::cout << "(4)-2 : " << input << std::endl;
  }
    return 0;
}


// (1) : "hello"
// (2) : 'hello'
// (3) : "hello"
// (4) : hello
// (4)-2 : hello


