/**
 * random sample
 * 2020-03-01 K.OHWADA
 */

// test for random.h
 // generate random int number 

#include <stdio.h>
#include "random.h"
 

/**
 * main
 */
int main(int argc, char *argv[])
{
    const int  NUM = 10;

    int  min = 0;
    int  max = 999;

    if(argc == 3){
            min = atoi(argv[1]);
            max = atoi(argv[2]);
    } else {
            printf("Usage: %s [min] [max] \n", argv[0]);
    }

    printf("random: %d  -> %d \n", min, max );


    for(int i=0; i<NUM; i++) {
        int num = genRandInt(min, max);
        printf(" %d \n", num);
    }

    return EXIT_SUCCESS;
}
