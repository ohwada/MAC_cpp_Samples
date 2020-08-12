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

    const int BUFSIZE = 10;
    char buf[BUFSIZE];

while(1)
{

  printf("Please enter string and return \n");
   printf(">"); // prompt

    int ret = getChars(buf, BUFSIZE);

    if(ret == INPUT_EMPTY){
        puts("empty");
        break;
    }else if(ret == INPUT_ERROR){
        puts("error");
    }

    printf("input: %s (%lu) \n", buf, strlen(buf) );

} // while

    return EXIT_SUCCESS;
}

