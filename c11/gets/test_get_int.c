/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// test for getInt

#include "input.h"


/**
 * main
 */
int main(void)
{

    enum Input in;

   int num =0;

    bool flag = false;

while(1)
{
    printf("Please enter int number and return \n");
   printf(">"); // prompt

   num = 0;
    in = getInt(&num);

    switch(in)
    {
        case SUCCESS:
            printf("input: %d \n", num);
            break;
        case EMPTY:
            puts("empty");
            flag = true;
            break;
        case ERROR:
            printf("error: %d \n", num);
            break;
    }

    if(flag){
        puts("goodby");
        break;
    }

} // while

    return EXIT_SUCCESS;
}

