#pragma once
/*
 * upper_lower.h
 * 2022-06-01 K.OHWADA 
*/

// reference : https://daeudaeu.com/lower_upper/

#include <stdbool.h>

// prototype
bool isAlphaNumerical(int c);
 bool isAlphabet(int c);
bool isUpper(int c);
bool isLower(int c);
bool isDigit(int c);
int toUpper(int c);
int toLower(int c);


/**
 * isAlphaNumerica
 */
bool isAlphaNumerical(int c)
{
    bool ret = (isAlphabet(c) || isDigit(c) )? true: false;
    return ret;
}


/**
 * isAlphabet
 */
 bool isAlphabet(int c)
{
    bool ret = ( isUpper(c) || isLower(c) )? true: false;
    return ret;
}


/**
 * isUpperer
 */
bool isUpper(int c)
{
    bool ret = ('A' <= c && c <= 'Z')? true : false;
    return ret;
}


/**
 * isLower
 */
bool isLower(int c)
{
    bool ret = ('a' <= c && c <= 'z')? true : false;
    return ret;
}


/**
 * isDigit
 */
bool isDigit(int c)
{
    bool ret = ('0' <= c && c <= '9')? true : false;
    return ret;
}


/**
 * toUpperer
 */
int toUpper(int c)
{
    if( isLower(c) ) {
        c = c - ('a' - 'A');
    }
    return c;
}


/**
 * toLower
 */
int toLower(int c)
{
    if( isUpper(c) ) {
        c = c + ('a' - 'A');
    }
    return c;
}


