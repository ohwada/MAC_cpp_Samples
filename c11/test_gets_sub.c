/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// test for gets_sub

#include "input.h"


/**
 * main
 */
int main(void)
{
    const int BUFSIZE = 10;
    char buf[BUFSIZE];

while(1)
{
    printf("Please enter string and return \n");
   printf(">"); // prompt

    if (gets_sub(buf) == NULL) {
        printf("fgets failed \n");
    }

    if( strlen(buf) == 0 ){
        break;
    }

    printf("input: %s ( %lu ) \n", buf, strlen(buf));

} // while

    return EXIT_SUCCESS;
}

