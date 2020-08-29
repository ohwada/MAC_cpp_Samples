#pragma once
/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// replace sub string in string
// reference : https://en.cppreference.com/w/cpp/string/basic_string/replace

#include <string>

// prototype
bool replaceString(std::string str, std::string s1,  std::string s2, std::string &dst);


/**
 *  replaceString
 */
bool replaceString(std::string str, std::string s1,  std::string s2, std::string &dst)
{

    std::string::size_type pos = str.find(s1);

    if (pos == std::string::npos) {
        return false;
    }
    
    dst = str;
    dst.replace(pos, s1.length(),  s2);

    return true;
}

