/**
 * sample3.c
 * 2022-06-01 K.OHWADA
 */

// This sample shows how binary data can be inserted into the string. 
// It also clears the string and prints new data into it.
// refrence : https://troydhanson.github.io/uthash/utstring.html

#include <stdio.h>
#include "utstring.h"

/**
 * main
 */
int main() {
    UT_string *s;
    char binary[] = "\xff\xff";

    utstring_new(s);
    utstring_bincpy(s, binary, sizeof(binary));
    printf("length is %u\n", utstring_len(s));

    utstring_clear(s);
    utstring_printf(s,"number %d", 10);
    printf("%s\n", utstring_body(s));

    utstring_free(s);
    return 0;
}

// length is 3
// number 10
