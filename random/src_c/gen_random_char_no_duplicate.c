/**
 * random sample
 * 2020-03-01 K.OHWADA
 */

// generate random chars
// that not duplicate character

#include<stdio.h>
#include "random_char.h"


/**
 * genRandomChars
 */
int genRandomChars(char* chars, int length, int flag)
{

    const int LIMIT = 100;
    const char END = 0;
    int ret = 0;

    chars[0] = END;

    for(int j=0; j<length; j++)
    {
        int cnt = 0;
        char c;

    while(1)
    {
        c = getRandomCharMix();

        // check duplicate
        if ( flag && strchr(chars, c) ) {
            // printf("duplicate %d : %c in %s \n", j, c, chars);
            ret = j;
            continue;
        } else {
            chars[j] = c;
            chars[j+1] = END;
            break;
        }

        cnt++;
        if(cnt > LIMIT) {
            ret = -1;
            break;
        }

    } // while

        chars[length] = END;
    } // for j

    return ret;
}


/**
 * getDuplicateChar
 */
int getDuplicateChar(char* chars )
{
    int len = strlen(chars);

    for(int j=0; j<len; j++)
    {
        char c1 = chars[j];
        for(int k=(j+1); k<len; k++)
        {
            char c2 = chars[k];
            // check duplicate
            if ( c1 == c2 ) {
                return c1;
            }
    } // for k
}// for j

    return 0;
}


/**
 * main
 */
int main(int argc, char *argv[])
{
    const int LENGTH = 10;
    const int NUM = 10;

    char chars[LENGTH+1];

    int flag = 1; // no duplicate

    if(argc == 2){
            flag = atoi(argv[1]);
    } else {
            printf(  "Usage: %s [flag]\n ", argv[0] );
    }

    for(int i=0; i<NUM; i++)
    {
        int ret = genRandomChars(chars, LENGTH, flag);
        printf("%s (%d) \n", chars, ret);
        int c = getDuplicateChar(chars );
        if(c != 0){
            printf("duplicate '%c' in %s \n", c, chars);
        }
    } // for i

    return EXIT_SUCCESS;
}


