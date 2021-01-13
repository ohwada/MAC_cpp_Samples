/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// sample for gets()
// gets() was deprecated in C11
// https://smartbear.de/blog/test-and-monitor/c11-a-new-c-standard-aiming-at-safer-programming/

// This program gives the following warning when running
// this program uses gets(), which is unsafe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * main
 */
int main(void)
{
    const int BUFSIZE = 10;
    char buf[BUFSIZE];

    printf("Please enter string and return \n");
   printf(">"); // prompt

// warning: this program uses gets(), which is unsafe
    if (gets(buf) == NULL) {
        printf("fgets faild \n");
    }

    printf("input: %s ( %lu ) \n", buf, strlen(buf));

    return EXIT_SUCCESS;
}

