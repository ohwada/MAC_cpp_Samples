#pragma once
/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// convert string to uppercase / lowercase
// reference : https://en.cppreference.com/w/cpp/algorithm/transform

#include<iostream>
#include <algorithm>
#include <cctype>

// protytype
char char2upper(char c);
char char2lower(char c);
void str2upper(std::string src, std::string &dst);
void str2lower(std::string src, std::string &dst);


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
void str2upper(std::string src, std::string &dst)
{

     dst.resize(src.size());

        std::transform(src.begin(), src.end(), dst.begin(), char2upper );

    return;
}


/**
 * str2lower
 */
void str2lower(std::string src, std::string &dst)
{

     dst.resize(src.size());

        std::transform(src.begin(), src.end(), dst.begin(), char2lower );

    return;
}

