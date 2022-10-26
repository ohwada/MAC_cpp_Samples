#pragma once
/**
 * response_parser
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// prototype
bool split_header_body(char* text, char* header, char* body);
size_t get_header_length(char* text);


/*
 *  split_header_body
*/
// prepare a large enough buffer of header and body
bool split_header_body(char* text, char* header, char* body)
{

    const char NUL = '\0';

    const char* delim = "\r\n\r\n"; 

// restore text
    char buf[strlen(text)+1];

    strcpy(buf, text);

    char* p = strstr(buf, delim);

    if(p==NULL){
        return false;
    }

    *p = NUL;

   strcpy( header, buf);
    strcpy( body, &p[4]);

    return true;
}


/*
 *  get_header_length
*/
// this function overwrites the input text
size_t get_header_length(char* text)
{

    const char NUL = '\0';

    const char* delim = "\r\n\r\n"; 

    char* p = strstr(text, delim);

    if(p==NULL){
        return 0;
    }

// overwrite text
    *p = NUL;

    return strlen(text);
}

