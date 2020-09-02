#pragma once
/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// replace sub string in string

#include <string>

// prototype
std::string replaceString(std::string str, std::string s1,  std::string s2);

std::string replaceString(std::string str, std::string s1,  std::string s2)
{

    std::string::size_type pos = str.find(s1);

    if (pos == std::string::npos) {
        return "";
    }
    
    str.replace(pos, s1.length(),  s2);

    return str;
}

