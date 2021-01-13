#pragma once
/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// get Chars / Int from stdin
 // substitute for gets()
// reference : https://ja.wikipedia.org/wiki/Fgets#gets_%E3%82%84_scanf_%E3%81%AE%E4%BB%A3%E6%9B%BF%E3%81%A8%E3%81%97%E3%81%A6%E7%94%A8%E3%81%84%E3%82%8B%E5%A0%B4%E5%90%88

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum Input {
    SUCCESS,
    EMPTY,
    ERROR
};

// prototyp
bool getInputChars(char* buf, size_t size);
char* gets_sub(char* buf);
bool getChars(char* buf, size_t size);
enum Input getInt(int *num);


/**
 * getInputChars
 */
bool getInputChars(char* buf, size_t size)
{

    const char LF = '\n' ;
    const char END = '\0' ;

    if (fgets(buf, size, stdin) == NULL) {
        return false;
    }

    if (strchr(buf, LF) != NULL) {
// if it contains a newline character
// replace with NUL terminal
        buf[strlen(buf) - 1] = END;
    } else {
// clear the input stream
// becuase the part exceeding the maximum number of characters are left in the input stream
        while(getchar() != LF);
        return false;
    }

    return true;
}


/**
 * gets_sub
 * substitute for gets()
 * adapted to api of gets
 * Parameters
 * str − this is the pointer to an array of chars where the C string is stored.
* Return Value
* this function returns 'buf' on success, 
 * and NULL on error or when end of file occurs, 
* while no characters have been read.
 * https://www.tutorialspoint.com/c_standard_library/c_function_gets.htm
 */ 
char* gets_sub(char* buf)
{

    size_t size = sizeof(buf);

    bool ret = getInputChars(buf, size);

    if(ret){
        return buf;
    } else {
        return NULL ;
    }

}


/**
 * getChars
 */
bool getChars(char* buf, size_t size)
{

    return getInputChars(buf, size);
}


/**
 * getInt
 * subsutitute for sscanf(buf, "%d", num)
 */
enum Input getInt(int *num)
{

    const size_t BUFSIZE = 10;
    char buf[BUFSIZE];

    bool res = false;

    bool ret1 = getInputChars(buf, BUFSIZE);
    if(ret1){
            if(strlen(buf) == 0){
                return EMPTY;
            }
            int ret2 = sscanf(buf, "%d", num);
            if(ret2 == 1){
                return SUCCESS;
            } 
    }

    return ERROR;
}

