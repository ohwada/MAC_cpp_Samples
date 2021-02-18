#pragma once
/**
 * C string sample
 * 2020-07-01 K.OHWADA
 */

// replace string

//  reference : https://qiita.com/edo_m18/items/4f69260d4ae3eaa68907


# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

// prototype
bool str_replace_all(const char *src, const char *target, const char *replace, char *result );
bool str_replace(const char *src, const char *target, const char *replace, char *result );


/**
 *  str_replace_all
 */
bool str_replace_all(const char *src, const char *target, const char *replace, char *result ) 
{

    const char CHAR_NULL = '\0';

    char temp[1024];
    char work[1024];
 
    // copy for operation
    strcpy(work, src);

    bool is_found = false;
    char *p;

    while(1)
    {
        p = strstr(work, target);
        if(p == NULL ){
            break;
        }

        is_found = true;

        // insert the string terminator at the detected position
        *p = CHAR_NULL;

        // move the pointer to the detected position + the number of target characters
        p += strlen(target);

        // save the character string and after to temp
        strcpy(temp, p);

        // concatenate the first half string and the replacement string
        strcat(work, replace);
        strcat(work, temp);
    } // while

    if(is_found ){
        strcpy(result, work);
    }

    return is_found;
}


/**
 *  str_replace
 */
bool str_replace(const char *src, const char *target, const char *replace, char *result ) 
{

    const char CHAR_NULL = '\0';

    char temp[1024];
    char work[1024];


    // copy for operation
    strcpy(work, src);

    char *p;

    p = strstr(work, target);
    if(p == NULL ){
            return false;
    }

        // insert the string terminator at the detected position
        *p = CHAR_NULL;

        // move the pointer to the detected position + the number of target characters
        p += strlen(target);

        // save the character string and after to temp
        strcpy(temp, p);

        // concatenate the first half string and the replacement string
        strcat(work, replace);
        strcat(work, temp);
        strcpy(result, work);

    return true;
}
