#pragma once
/**
 * C string sample
 * 2020-07-01 K.OHWADA
 */

// convert string to uppercase / lowercase


#include <string.h>
#include <ctype.h>

// protytype
char char2upper(char c);
char char2lower(char c);
void str2upper(char *src, char *dst);
void str2lower(char *src, char *dst);


/**
 * char2upper
 */
char char2upper(char c) 
{
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
char char2lower(char c) 
{
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
void str2upper(char *src, char *dst)
{

    size_t size = strlen(src);
    for(int i=0; i<size; i++){
        dst[i] = char2upper( src[i] ); 
    }

}


/**
 * str2lower
 */
void str2lower( char *src,  char *dst)
{

    size_t size = strlen(src);
    for(int i=0; i<size; i++){
        dst[i] = char2lower( src[i] ); 
    }

}

