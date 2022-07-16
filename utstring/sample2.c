/**
 * sample2.c
 * 2022-06-01 K.OHWADA
 */

// This sample demonstrates that utstring_printf appends to the string. 
// It also shows concatenation.
// reference : https://troydhanson.github.io/uthash/utstring.html

#include <stdio.h>
#include "utstring.h"

/**
 * main
 */
int main() {
    UT_string *s, *t;

    utstring_new(s);
    utstring_new(t);

    utstring_printf(s, "hello " );
    utstring_printf(s, "world " );

    utstring_printf(t, "hi " );
    utstring_printf(t, "there " );

    utstring_concat(s, t);
    printf("length: %u\n", utstring_len(s));
    printf("%s\n", utstring_body(s));

    utstring_free(s);
    utstring_free(t);
    return 0;
}

// length: 21
// hello world hi there 
