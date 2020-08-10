 #pragma once
/**
 * random sample
 * 2020-03-01 K.OHWADA
 */

// generate random char with rand.h
// reference : https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c

#include<string.h>

#include "rand.h"


// prototype
char choseRandomChar(const char* chars);
char getRandomCharMix(void);
char getRandomCharLower(void);
char getRandomCharUpper(void);
char getRandomCharDegit(void);
char getRandomCharSpecial(void) ;


/**
 * choseRandomChar
 */
char choseRandomChar(const char* chars)
{

    int max = strlen(chars) -1;
    int index = genRand(0, max);
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
 * getRandomCharDegit
 */
char getRandomCharDegit(void)
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

