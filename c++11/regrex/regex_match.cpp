/**
 * regex_match.cpp
 * 2022-06-01 K.OHWADA
 */

// https://cpprefjp.github.io/reference/regex/regex_match.html

/**
  (1) 
bool regex_match(BidirectionalIterator first, BidirectionalIterator last,
                   match_results<BidirectionalIterator, Allocator>& m,
                   const basic_regex<charT, traits>& e,
                   regex_constants::match_flag_type flags = regex_constants::match_default);

Determine whether the entire string specified by [first, last) matches the regular expression specified by e.
flags specify how the regular expression matches against strings.


(2)
  bool regex_match(const charT* str,
                   match_results<const charT*, Allocator>& m,
                   const basic_regex<charT, traits>& e,
                   regex_constants::match_flag_type flags = regex_constants::match_default);          // (2)

Equivalent to return regex_match(str, str + char_traits::length(str), m, e, flags).


(3)
  bool regex_match(const basic_string<charT, ST, SA>& s,
                   match_results<typename basic_string<charT, ST, SA>::const_iterator, Allocator>& m,
                   const basic_regex<charT, traits>& e,
                   regex_constants::match_flag_type flags = regex_constants::match_default);          

Equivalent to return regex_match(s.begin(), s.end(), m, e, flags)
**/

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
    std::cout << "(1) " << std::regex_match(std::begin(s), std::end(s), m, std::regex("\\w+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

  {

    std::cmatch m;
    std::cout << "(2) " << std::regex_match("abc123def", m, std::regex("\\w+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

  {
    const std::string s = "abc123def";
    std::smatch m;
    std::cout << "(3) " << std::regex_match(s, m, std::regex("\\w+")) << std::endl;
    std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

 {
    //std::smatch m;
    //std::cout << "(4) " << std::regex_match(std::string("abc123def"), m, std::regex("\\w+")) << std::endl;
    //std::cout << "str = '" << m.str() << "', position = " << m.position() << std::endl;
  }

  {
    const std::list<char> s = { 'a', 'b', 'c', '1', '2', '3', 'd', 'e', 'f' };
    std::cout << "(5) " << std::regex_match(std::begin(s), std::end(s), std::regex("\\w+")) << std::endl;
  }

  {
    std::cout << "(6) " << std::regex_match("abc123def", std::regex("\\w+")) << std::endl;
  }

  {
    const std::string s = "abc123def";
    std::cout << "(7)-1 " << std::regex_match(s, std::regex("\\w+")) << std::endl;
  }

  {
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
//(7)-2 true

