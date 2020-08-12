/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// sample for scanf()

#include <stdio.h>
#include <stdlib.h>


/**
 * main
 */
int main(void)
{

    int key;

while(1)
{
    printf("Please enter int number and return \n");
   printf(">"); // prompt

    int ret = scanf("%d", &key);

// TODO: 
// on error,
// repeat from input prompt 
// without exiting loop
     if(ret != 1){
// On error,
// key is the previous value
        printf("error: %d \n", key);
        break;
    }

// TODO: 
// exit the loop when return key
    if(key == 0){
        break;
    }

    printf("input: %d \n", key);

} // while

    return EXIT_SUCCESS;
}

