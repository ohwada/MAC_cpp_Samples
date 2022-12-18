/**
 * regex_search.cpp
 * 2022-06-01 K.OHWADA
 */

// https://cpprefjp.github.io/reference/regex/regex_search.html

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
    const std::list<char> s = { 'a', 'b', 'c', '1', '2', '3', 'd', 'e', 'f' };
    std::match_results<std::list<char>::const_iterator> m;
    std::cout << "(1) " << std::regex_search(std::begin(s), std::end(s), m, std::regex("\\d+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

  {
    std::cmatch m;
    std::cout << "(2) " << std::regex_search("abc123def", m, std::regex("\\d+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

  {
    const std::string s = "abc123def";
    std::smatch m;
    std::cout << "(3) " << std::regex_search(s, m, std::regex("\\d+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

  {
    //std::smatch m;
    //std::cout << "(4) " << std::regex_search(std::string("abc123def"), m, std::regex("\\d+")) << std::endl;
    //std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

  {
    const std::list<char> s = { 'a', 'b', 'c', '1', '2', '3', 'd', 'e', 'f' };
    std::cout << "(5) " << std::regex_search(std::begin(s), std::end(s), std::regex("\\d+")) << std::endl;
  }

  {
    std::cout << "(6) " << std::regex_search("abc123def", std::regex("\\d+")) << std::endl;
  }

  {
    const std::string s = "abc123def";
    std::cout << "(7)-1 " << std::regex_search(s, std::regex("\\d+")) << std::endl;
  }

  {
    std::cout << "(7)-2 " << std::regex_search(std::string("abc123def"), std::regex("\\d+")) << std::endl;
  }

    return 0;
}

// (1) true
// str = '123', position = 3
// (2) true
// str = '123', position = 3
// (3) true
// str = '123', position = 3
// (5) true
// (6) true
// (7)-1 true
// (7)-2 true
