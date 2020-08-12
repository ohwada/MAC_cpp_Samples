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

    int num;

while(1)
{
    printf("Please enter int number and return \n");
   printf(">"); // prompt

    int ret = getInt(&num);

     if(ret == INPUT_EMPTY){
        puts("empty");
        break;
    }else if(ret == INPUT_ERROR){
        printf("error: %d \n", num);
        continue;
    }

    printf("input: %d \n", num);

} // while

    return EXIT_SUCCESS;
}

