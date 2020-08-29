#pragma once
/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */


// get the substring sandwiched by the specified words from the string
// reference : https://en.cppreference.com/w/cpp/string/basic_string/substr

#include <string>

bool subString( std::string str, std::string s1, std::string s2, std::string &sub,  std::string &head,  std::string &tail);

/** 
 * subString
  */
bool subString( std::string src, std::string s1, std::string s2, std::string &sub,  std::string &head,  std::string &tail)
{

  std::string::size_type pos1 = src.find(s1);
    if (pos1 == std::string::npos) {
            sub = "";
            return false;
    }


  std::string::size_type pos2 = src.find(s2);
    if (pos2 == std::string::npos) {
            sub = "";
            return false;
    }

 
    int start = pos1 + s1.size();
    int len = pos2 - start;

    sub = src.substr(start, len);


    int head_len = pos1;

    head = src.substr(0, head_len);

    int tail_start = pos2 + s2.size();
    int tail_len = src.size() - tail_start ;

    tail = src.substr(tail_start, tail_len);

    return true;
}
