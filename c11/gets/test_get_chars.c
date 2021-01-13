/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// test for getChars

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

    bool ret = getChars(buf, BUFSIZE);

    if(ret){
        size_t len = strlen(buf);
        printf("input: %s (%lu) \n", buf, len );
        if(len == 0){
            puts("goodby");
            break;
        }
    } else {
        puts("input error");
    }

} // while

    return EXIT_SUCCESS;
}

