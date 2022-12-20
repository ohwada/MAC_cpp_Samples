/**
 * test_random_char.c
 * 2020-03-01 K.OHWADA
 */

// test for random_char.h
// generate random chars

#include<stdio.h>

#include "random_char.h"


/**
 * getRandomChar(
 */
char getRandomChar(int mode)
{

    char c = 0;
    switch(mode)
    {
    case 1:
            c = getRandomCharMix();
            break;
    case 2:
            c = getRandomCharLower();
            break;
    case 3:
           c = getRandomCharUpper();
            break;
    case 4:
           c = getRandomCharDigit();
            break;
    case 5:
           c = getRandomCharSpecial();
            break;
    }

    return c;
}


/**
 * main
 */
int main(int argc, char *argv[])
{
    const int LENGTH = 10;
    const int NUM = 10;

    char chars[LENGTH+1];

    int mode = 1; // upper lower mix

    if(argc == 2){
            mode = atoi(argv[1]);
    } else {
            printf(  "Usage: %s [mode ]\n ", argv[0] );
    }

    switch(mode)
    {
        case 1:
            printf( "mode 1: mix lowercase upercase degit \n");
            break;
        case 2:
            printf("mode 2: lowercase \n");
            break;
        case 3: 
            printf( "mode 3: uppercase \n");
            break;
       case 4:
            printf( "mode 4: degit \n");
            break;
       case 5: 
            printf( "mode 5: special \n");
            break;
        default:
            printf( "mode must be from 1 to 5 \n");
            return 1;
    }


    for(int i=0; i<NUM; i++)
    {
        for(int j=0; j<LENGTH; j++)
        {
            char c = getRandomChar(mode);
            chars[j] = c;
        } // for j

        chars[LENGTH] = 0;
        printf("%s \n", chars);
    } // for i

    return 0;
}

