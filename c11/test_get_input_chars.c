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

    const int BUFSIZE = 10;
    char buf[BUFSIZE];

    enum Input in;

while(1)
{

  printf("Please enter string and return \n");
   printf(">"); // prompt

    in = getInputChars(buf, BUFSIZE);

    int flag = 0;
    switch(in)
    {
        case SUCCESS:
            printf("input: %s \n", buf);
            break;
        case EMPTY:
            puts("empty");
            flag = 1;
            break;
        case ERROR:
            puts("error");
            break;
         case OVER:
            printf("over: %s (%lu) \n", buf, strlen(buf) );
            break;
    }

    if(flag){
        break;
    }

} // while

    return EXIT_SUCCESS;
}

