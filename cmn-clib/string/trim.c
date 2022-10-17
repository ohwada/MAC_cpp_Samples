/**
 * trim.c
 * 2022-06-01 K.OHWADA
 */

// Remove spaces at both ends of string

// reference : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnString.c

// CmnString_RTrim 
// https://ityorozu.net/dev/cmn-clib/doc/html/de/dba/_cmn_string_8h.html#aacbceb28d2e602e5d12697fe3ede3704

// CmnString_LTrim 
// https://ityorozu.net/dev/cmn-clib/doc/html/de/dba/_cmn_string_8h.html#aaacf01fe078fc72bfb6e9e471e46afba

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cmnclib/CmnString.h"

int main()
{

char nonSpace[]    = "Hello world";

	char singleSpace[] = " Hello world ";

    printf("|%s| \n",  singleSpace);

    char* str1 = CmnString_RTrim(singleSpace);
    char* str2 = CmnString_LTrim(str1);

    printf("|%s| \n", str1);
    printf("|%s| \n", str2);

    assert( strcmp(str2, nonSpace) == 0);

    printf("successful \n");

    return 0;
}

// | Hello world | 
// | Hello world| 
// |Hello world|


