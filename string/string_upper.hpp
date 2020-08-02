/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// convert string to uppercase / lowercase

#include<iostream>
#include <algorithm>
#include <cctype>

#ifndef _H_STRING_UPPER_H_
#define __H_STRING_UPPER_H_

// protytype
char char2upper(char c);
char char2lower(char c);
std::string str2upper(std::string src);
std::string str2lower(std::string src);


/**
 * char2upper
 */
char char2upper(char c) {
    char ret;
    if(isalpha(c)) {
        ret = toupper(c);
    } else {
        ret = c;
    }
    return ret;
}


/**
 * char2lower
 */
char char2lower(char c) {
    char ret;
    if(isalpha(c)) {
        ret = tolower(c);
    } else {
        ret = c;
    }
    return ret;
}


/**
 * str2upper
 */
std::string str2upper(std::string src)
{
    std::string dst;
     dst.resize(src.size());

        std::transform(src.begin(), src.end(), dst.begin(), char2upper );

    return dst;
}


/**
 * str2lower
 */
std::string str2lower(std::string src)
{
    std::string dst;
     dst.resize(src.size());

        std::transform(src.begin(), src.end(), dst.begin(), char2lower );

    return dst;
}

#endif // _H_STRING_UPPER_H_
