#pragma once
/**
 * request_parser.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<regex.h>

// prototype
bool parse_path(char* request,  char* path);


/**
 *  parse_path
 */
bool parse_path(char* text,  char* result)
{
    const char NUL = '\0';

    const char PATTERN[] =  "GET (/.*) HTTP";

  const size_t MATCH_SIZE = 4;
const size_t BUFSIZE = 100;

    regmatch_t match[MATCH_SIZE];
char buf[MATCH_SIZE][BUFSIZE];

    regex_t regexBuffer;

    // Compile regular expression object
    if ( regcomp(&regexBuffer, PATTERN, REG_EXTENDED | REG_NEWLINE ) != 0 )
    {
        printf("regcomp failed\n");
        return false;
    }

    // match a regex PATTERN?
    if ( regexec(&regexBuffer, text, MATCH_SIZE, match, 0) != 0 )
    {
        //printf("no match\n");
        return false;
    }

    for(int i=0; i<MATCH_SIZE; i++)
    {
            for(int j=0; j<BUFSIZE; j++){
                buf[i][j] = NUL;
            } // for j       
    } // for i

    // What to do if the PATTERN matches
    for ( int i = 0; i < MATCH_SIZE; i++ )
    {
        // start/end index of matched position
        int startIndex = match[i].rm_so; 
        int endIndex = match[i].rm_eo; 
        if ( startIndex == -1 || endIndex == -1 )
        {
            continue;
        }
        //printf("index [start, end] = %d, %d\n", startIndex, endIndex);
        strncpy(buf[i], text + startIndex, endIndex - startIndex);
        //printf("%d: %s \n", i, buf[i]);
    } // for

    regfree(&regexBuffer);

    strcpy(result, buf[1]);

    return true;
}

