/**
 * random sample
 * 2022-06-01 K.OHWADA
 */

// generate random password with random_string.hpp


#include "random_string.hpp"
 
// prototype
std::string genPasswd(int len_lower, int len_upper, int  len_digit, int len_special, int len_mix);
std::string shuffle( std::string text);


/**
 * genPasswd
 */
std::string genPasswd(int len_lower, int len_upper, int  len_digit, int len_special, int len_mix) 
{
    std::string text = 
    genRandomStringLower(len_lower)
    + genRandomStringUpper(len_upper)
    + genRandomStringDigit(len_digit)
    + genRandomStringSpecial(len_special) 
	+ genRandomStringMix(len_mix);
    return text;
}


/**
 * genPasswd
 */
std::string shuffle( std::string text)
{
	std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(text.begin(), text.end(), mt);
    return text;
}

