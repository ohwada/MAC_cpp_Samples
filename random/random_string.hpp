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
std::string genRandomStringDigit(int length);
std::string genPasswd(int len_lower, int len_upper, int  len_digit, int len_special);


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
 * genRandomStringDigit
 */
std::string genRandomStringDigit(int length) 
{
    std::string text(length, '.');
 
    generate_n(text.begin(), length,  getRandomCharDigit );
 
    return text;
}


/**
 * genPasswd
 * mix lowercase uppercase degit specialchar
 */
std::string genPasswd(int len_lower, int len_upper, int  len_digit, int len_special) 
{

    std::string str_special(len_special, '.');

    generate_n(str_special.begin(), len_special,  getRandomCharSpecial );

    std::string text = 
    genRandomStringLower(len_lower)
    + genRandomStringUpper(len_upper)
    + genRandomStringDigit(len_digit)
    + str_special ;

    return text;
}

