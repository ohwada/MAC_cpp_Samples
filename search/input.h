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
#include <string.h>


#define INPUT_SUCCESS 0
#define INPUT_EMPTY 1
#define INPUT_ERROR 2


enum Input {
    SUCCESS,
    EMPTY,
    OVER,
    ERROR,
};


// prototype
enum Input getInputChars(char* buf, int size);
char* gets_sub(char* buf);
int getChars(char* buf, int size);
int getInt(int *key);


/**
 * getInputChars
 */
enum Input getInputChars(char* buf, int size)
{

    const char LF = '\n' ;
    const char END = '\0' ;

    if (fgets(buf, size, stdin) == NULL) {
        return ERROR;
    }

    if (strchr(buf, LF) != NULL) {
// if it contains a newline character
// replace with NUL terminal
        buf[strlen(buf) - 1] = END;
    } else {
// clear the input stream
// becuase the part exceeding the maximum number of characters are left in the input stream
        while(getchar() != LF);
        return OVER;
    }

    if( strlen(buf) == 0 ){
        return EMPTY;
    }

    return SUCCESS;
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

    int size = sizeof(buf);

    enum Input in;
    in = getInputChars(buf, size);

    switch(in)
    {
        case SUCCESS:
            break;
        case EMPTY:
            break;
        case ERROR:
            return NULL;
        case OVER:
            return NULL;
    } // switch

    return buf;
}


/**
 * getChars
 */
int getChars(char* buf, int size)
{

    enum Input in;
    in = getInputChars(buf, size);

    switch(in)
    {
        case SUCCESS:
            break;
        case EMPTY:
            return INPUT_EMPTY;
        case ERROR:
            return INPUT_ERROR;
        case OVER:
            return INPUT_ERROR;
    } // switch

    return INPUT_SUCCESS;
}


/**
 * getInt
 * subsutitute for sscanf(buf, "%d", key)
 */
int getInt(int *key)
{

    const int BUFSIZE = 10;
    char buf[BUFSIZE];

    enum Input in;
    in = getInputChars(buf, BUFSIZE);

    switch(in)
    {
        case SUCCESS:
            break;
        case EMPTY:
            return INPUT_EMPTY;
        case ERROR:
            return INPUT_ERROR;
        case OVER:
            return INPUT_ERROR;
    } // switch

    int ret = sscanf(buf, "%d", key);
    if(ret != 1){
            return INPUT_ERROR;
    }

    return INPUT_SUCCESS;
}

