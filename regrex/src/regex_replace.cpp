/**
 * regex_replace.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ regex_replace.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/regex/regex_replace.html

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
  {
    // case (1) 
    const std::list<char> s = { 'a', 'b', 'c', '0', '1', '2', 'd', 'e', 'f' };
    const std::regex re("\\d+");
    const std::string fmt = "[$&]";
    std::cout << "(1) '";
    std::regex_replace(std::ostream_iterator<char>(std::cout), std::begin(s), std::end(s), re, fmt);
    std::cout << '\'' << std::endl;
  }
  {
    // case (2) 
    const std::list<char> s = { 'a', 'b', 'c', '0', '1', '2', 'd', 'e', 'f' };
    const std::regex re("\\d+");
    const char fmt[] = "[$&]";
    const std::regex_constants::match_flag_type flags = std::regex_constants::format_no_copy;
    std::cout << "(2) '";
    std::regex_replace(std::ostream_iterator<char>(std::cout), std::begin(s), std::end(s), re, fmt, flags);
    std::cout << '\'' << std::endl;
  }
  {
    // case (3) 
    const std::string s = "abc123def456ghi";
    const std::regex re("\\d+");
    const std::string fmt = "[$&]";
    std::cout << "(3) '" << std::regex_replace(s, re, fmt) << '\'' << std::endl;
  }
  {
    // case (4) 
    const std::string s = "abc123def456ghi";
    const std::regex re("\\d+");
    const char fmt[] = "[$&]";
    const std::regex_constants::match_flag_type flags = std::regex_constants::format_first_only;
    std::cout << "(4) '" << std::regex_replace(s, re, fmt, flags) << '\'' << std::endl;
  }
  {
    // case (5) 
    const char s[] = "abc123def456ghi";
    const std::regex re("(\\d)(\\d)(\\d)");
    const std::string fmt = "[$3$2$1]";
    std::cout << "(5) '" << std::regex_replace(s, re, fmt) << '\'' << std::endl;
  }
  {
    // case (6) 
    const char s[] = "abc123def456ghi";
    const std::regex re("(\\d)(\\d)(\\d)");
    const char fmt[] = "[\\3\\2\\1]";
    const std::regex_constants::match_flag_type flags = std::regex_constants::format_sed;
    std::cout << "(6) '" << std::regex_replace(s, re, fmt, flags) << '\'' << std::endl;
  }

    return 0;
}


// (1) 'abc[012]def'
// (2) '[012]'
// (3) 'abc[123]def[456]ghi'
// (4) 'abc[123]def456ghi'
// (5) 'abc[321]def[654]ghi'
// (6) 'abc[321]def[654]ghi'

