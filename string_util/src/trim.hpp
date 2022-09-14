/**
 * trim.hpp
 * 2022-06-01 K.OHWADA
 */

// https://www.techiedelight.com/ja/trim-string-cpp-remove-leading-trailing-spaces/

#include <string>
#include <algorithm>

// prototype 
std::string trim(const std::string &s) ;
std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);

const std::string WHITESPACE = " \n\r\t\f\v";


/**
 * trim
 */
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}


/**
 * ltrim
 */
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}


/**
 * rtrim
 */
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

