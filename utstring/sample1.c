/**
 * sample1.c
 * 2022-06-01 K.OHWADA
 */

// This samples show how to use utstring.
// reference : https://troydhanson.github.io/uthash/utstring.html

#include <stdio.h>
#include "utstring.h"

/**
 * main
 */
int main() {
    UT_string *s;

    utstring_new(s);
    utstring_printf(s, "hello world!" );
    printf("%s\n", utstring_body(s));

    utstring_free(s);
    return 0;
}

// hello world!
