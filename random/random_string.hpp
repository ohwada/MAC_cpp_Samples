#pragma once
/**
 * random sample
 * 2020-03-01 K.OHWADA
 */

// generate random string with random_char.h
// reference : https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
// reference: https://code.sololearn.com/cZCsi2DPMCpy/#cpp


#include <string>
#include <algorithm>

#include "random_char.h"


// prototype
std::string genRandomStringMix(int length);
std::string genRandomStringLower(int length);
std::string genRandomStringUpper(int length);
std::string genRandomStringDegit(int length);
std::string genPasswd(int len_lower, int len_upper, int len_number, int len_special);


/**
 * genRandomStringMix
 * mix lowercasw uppercase degit
 */
std::string genRandomStringMix(int length) 
{
    std::string text(length, '.');
 
    generate_n(text.begin(), length,  getRandomCharMix );
 
    return text;
}


/**
 * genRandomStringUpper
 */
std::string genRandomStringUpper(int length) 
{
    std::string text(length, '.');
 
    generate_n(text.begin(), length,  getRandomCharUpper );
 
    return text;
}


/**
 * genRandomStringLower
 */
std::string genRandomStringLower(int length) 
{
    std::string text(length, '.');
 
    generate_n(text.begin(), length,  getRandomCharLower );
 
    return text;
}


/**
 * genRandomStringDegit
 * mix lower upper number
 */
std::string genRandomStringDegit(int length) 
{
    std::string text(length, '.');
 
    generate_n(text.begin(), length,  getRandomCharDegit );
 
    return text;
}


/**
 * genPasswd
 * mix lowercase uppercase degit specialchar
 */
std::string genPasswd(int len_lower, int len_upper, int len_number, int len_special) 
{

    std::string str_lower(len_lower, '.');
    std::string str_upper(len_upper, '.');
    std::string str_number(len_number, '.');
    std::string str_special(len_special, '.');

    generate_n(str_lower.begin(), len_lower,  getRandomCharLower );
 
    generate_n(str_upper.begin(), len_upper,  getRandomCharUpper );

    generate_n(str_number.begin(), len_number,  getRandomCharDegit );

    generate_n(str_special.begin(), len_special,  getRandomCharSpecial );

    std::string text = str_upper 
    + str_lower
    + str_special
    + str_number;

    return text;
}

