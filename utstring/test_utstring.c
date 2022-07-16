/**
 * test_utstring.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/zinbe/items/224e24e77755d8c54e96

#include <stdio.h>
#include "utstring.h"


/**
 * main
 */
int main() 
{

// create new
    UT_string *s;
    utstring_new(s);  
// store string
    utstring_printf(s, "number=%d", 123);
    printf("%s\n", utstring_body(s)); // number=123

    char *str = "hoge";
// create new
    UT_string *t;
    utstring_new(t);
// copy string from char* str
    utstring_bincpy(t, str, strlen(str));   
    printf("%s\n", utstring_body(t)); // hoge

// connect t to s
    utstring_concat(s, t);
    printf("%s\n", utstring_body(s)); // number=123hoge

// release
    utstring_free(s);
    utstring_free(t);

	return 0;
}


// number=123
// hoge
// number=123hoge
