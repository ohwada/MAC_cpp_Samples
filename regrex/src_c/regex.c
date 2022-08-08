/**
 * regex.c
 * 2022-06-01 K.OHWADA
 */

// refence : https://www.lisz-works.com/entry/c-regex

#include <stdio.h>
#include <string.h>
#include <regex.h>


/**
 * main
 */
int main(void)
{
    const char TEXT[]= "abc-xyz-0001.dat";
    const char PATTERN[] = "xyz-[0-9]{4}\\.dat";

    const int SIZE = 4;
    regmatch_t match[SIZE];
    
    const int BUFSIZE = 128;
    char result[BUFSIZE];

    regex_t regexBuffer;

    // Compile regular expression object
    if ( regcomp(&regexBuffer, PATTERN, REG_EXTENDED | REG_NEWLINE ) != 0 )
    {
        printf("regcomp failed\n");
        return 1;
    }

    // match a regex PATTERN?
    if ( regexec(&regexBuffer, TEXT, SIZE, match, 0) != 0 )
    {
        printf("no match\n");
        return 1;
    }

    // What to do if the PATTERN matches
    for ( int i = 0; i < SIZE; i++ )
    {
        // start/end index of matched position
        int startIndex = match[i].rm_so; 
        int endIndex = match[i].rm_eo; 
        if ( startIndex == -1 || endIndex == -1 )
        {
            continue;
        }
        printf("index [start, end] = %d, %d\n", startIndex, endIndex);
        strncpy(result, TEXT + startIndex, endIndex - startIndex);
        printf("%s\n", result);
    } // for

    regfree(&regexBuffer);
    return 0;
}


// index [start, end] = 4, 16
// xyz-0001.dat


