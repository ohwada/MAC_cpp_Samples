#pragma once
/**
 * random sample
 * 2022-06-01 K.OHWADA
 */

// generate random string with random_char.h
// reference : https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
// reference: https://code.sololearn.com/cZCsi2DPMCpy/#cpp


#include <string>
#include <algorithm>
#include <string.h>
#include "rand.hpp"


// prototype
std::string genRandomStringMix(int length);
std::string genRandomStringLower(int length);
std::string genRandomStringUpper(int length);
std::string genRandomStringDigit(int length);
std::string genRandomStringSpecial(int length);
char choseRandomChar(const char* chars);
char getRandomCharMix(void);
char getRandomCharLower(void);
char getRandomCharUpper(void);
char getRandomCharDigit(void);
char getRandomCharSpecial(void) ;


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
 * genRandomStringSpecial
 */
std::string genRandomStringSpecial(int length) 
{
    std::string text(length, '.');
 
    generate_n(text.begin(), length,  getRandomCharSpecial );
 
    return text;
}


// === same as randm_char.h  ===


/**
 * choseRandomChar
 */
char choseRandomChar(const char* chars)
{

    int max = strlen(chars) -1;
    int index = genRandInt(0, max);
    char c = chars[index];
    return c;
}


/**
 * getRandomCharMix
 * mix lowercasw uppercase degit
 */
char getRandomCharMix(void)
{
    const char CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    char c = choseRandomChar(CHARS);
    return c;
}


/**
 * getRandomCharLower
 */
char getRandomCharLower(void)
{
    const char CHARS[] = "abcdefghijklmnopqrstuvwxyz";

    char c = choseRandomChar(CHARS);

    return c;
}


/**
 * getRandomCharUpper
 */
char getRandomCharUpper(void)
{
    const char CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char c = choseRandomChar(CHARS);

    return c;
}


/**
 * getRandomCharDigit
 */
char getRandomCharDigit(void)
{
    const char CHARS[] = "01234567890123456789";

    char c = choseRandomChar(CHARS);

    return c;
}

 
/**
 * getRandomCharSpecial
 */
char getRandomCharSpecial(void) 
{

    char  CHARS[] = "!@#$%~^&*()-=_+[]{}\\|;:'\"<>,.?/";

   char c = choseRandomChar(CHARS);

    return c;
}

