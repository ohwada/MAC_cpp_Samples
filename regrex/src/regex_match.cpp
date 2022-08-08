/**
 * regex_match.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ regex_match.cpp -std=c++11

// reference : https://cpprefjp.github.io/reference/regex/regex_match.html

#include <iostream>
#include <iterator>
#include <list>
#include <regex>
#include <string>


/**
 * main
 */
int main()
{
  std::cout << std::boolalpha;
  {
    // case (1)
    const std::list<char> s = { 'a', 'b', 'c', '1', '2', '3', 'd', 'e', 'f' };
    std::match_results<std::list<char>::const_iterator> m;
    std::cout << "(1) " << std::regex_match(std::begin(s), std::end(s), m, std::regex("\\w+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }
  {
    // case (2) 
    std::cmatch m;
    std::cout << "(2) " << std::regex_match("abc123def", m, std::regex("\\w+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }
  {
    // case (3) 
    const std::string s = "abc123def";
    std::smatch m;
    std::cout << "(3) " << std::regex_match(s, m, std::regex("\\w+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }
  {
    // case (4) 
// Uncommenting will result in an error in C++14
    //std::smatch m;
    //std::cout << "(4) " << std::regex_match(std::string("abc123def"), m, std::regex("\\w+")) << std::endl;
    //std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }
  {
    // case (5) 
    const std::list<char> s = { 'a', 'b', 'c', '1', '2', '3', 'd', 'e', 'f' };
    std::cout << "(5) " << std::regex_match(std::begin(s), std::end(s), std::regex("\\w+")) << std::endl;
  }
  {
    // case (6) 
    std::cout << "(6) " << std::regex_match("abc123def", std::regex("\\w+")) << std::endl;
  }
  {
    //case  (7)-1
    const std::string s = "abc123def";
    std::cout << "(7)-1 " << std::regex_match(s, std::regex("\\w+")) << std::endl;
  }
  {
    // case (7)-2
    std::cout << "(7)-2 " << std::regex_match(std::string("abc123def"), std::regex("\\w+")) << std::endl;
  }

    return 0;
}

// (1) true
// str = 'abc123def', position = 0
// (2) true
// str = 'abc123def', position = 0
// (3) true
// str = 'abc123def', position = 0
// (5) true
// (6) true
// (7)-1 true
// (7)-2 true


