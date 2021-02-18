/**
 * C string sample
 * 2021-02-01 K.OHWADA
 */

// replace all characters in a string

// gcc replace_char_all.c 

// reference : https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1096838730

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototype
void  replace_char_all( char *src, char *result, char target, char replace);


/**
 *   replace_char_all
 */

void  replace_char_all( char *src, char *result, char target, char replace)
{

    char *p;

    strcpy(result, src);

    while ( (p = strchr(result, target)) != NULL ) {
        *p = replace;
    }
}


/**
 *  main
 */

int main (void)
{

    const char src[] = {"ABCDEFGAabcdefgaAdDAW"};

    const char TARGET = 'A';

    const char REPLACE = '_';

    char result[100];




    printf("%s\n", src);

    replace_char_all( (char *)src, (char *)result, TARGET, REPLACE );

    printf("%s\n", result);

    return EXIT_SUCCESS;
}

