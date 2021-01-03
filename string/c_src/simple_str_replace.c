/**
 * string sample
 * 2020-07-01 K.OHWADA
 */

// replace string 
// simple example that makes the processing flow easy to understand

// try test_str_replace.c
// header only library version
// the algorithm is the same

// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/01/03/114140


# include <stdio.h>


/**
 *  main
 */
int main(void) 
{

// string terminator
    const char CHAR_NULL = '\0';

    char src[] = "foo bar fiz";

// replace bar to xyz
    char *target  = "bar";
    char *replace = "xyz";

    char work[100];
    char tail[100];
    char result[100];

    printf("src: %s\n", src);

    // copy for operation
    strcpy(work, src);

    char *p;

// find the first occurrence of the substring target in the string work
// return a pointer to the first occurrence in work
    p = strstr(work, target);

    if(p == NULL ){
            fprintf(stderr, "not found: %s \n", target); 
            return EXIT_FAILURE;
    }

    // insert the string terminator at the detected position
    *p = CHAR_NULL;

    printf("work: %s \n", work); 

    // move the pointer to the detected position + the number of target characters
        p += strlen(target);

        // save the string to tail
        strcpy(tail, p);
        printf("tail: %s \n", tail); 

        // concatenate the first half string and the replacement string
    strcpy(result, work);
    strcat(result, replace);
    strcat(result, tail);

    printf("result: %s\n", result); 

    return EXIT_SUCCESS;
}
