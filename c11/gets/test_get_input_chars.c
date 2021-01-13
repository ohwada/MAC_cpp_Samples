/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// test for getInputChars

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

    bool ret = getInputChars(buf, BUFSIZE);
    if(ret){
        if(strlen(buf) == 0){
            printf("goodby \n");
            break;
        }
        printf("input: %s \n", buf);
    } else {
        fprintf(stderr, "input error \n");
    }

} // while

    return EXIT_SUCCESS;
}


// Please enter string and return 
// >abc
// input: abc 

