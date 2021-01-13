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
    const size_t BUFSIZE = 10;
    char buf[BUFSIZE];

while(1)
{
    printf("Please enter string and return \n");
   printf(">"); // prompt

    char *line = gets_sub(buf);
    if (line == NULL) {
        printf("fgets failed \n");
    } else {
        size_t len = strlen(buf)
        printf("input: %s ( %lu ) \n", buf, len);
        if( len == 0 ){
            printf("goodby \n");
            break;
        }
    }

} // while

    return EXIT_SUCCESS;
}

