/**
 * c++ sample
 * 2020-03-01 K.OHWADA
 */

// test for str_upper.h


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "str_upper.h"
# include "input.h"

/**
 *  main
 */
int main(int argc, char *argv[])
{

    int mode = 1; // upper

    if(argc == 2){
            mode = atoi(argv[1]);
    } else {
            printf("Usage: %s [mode] \n", argv[0] );
    }


    char msg[100];

    if(mode == 1){
        strcpy(msg, "please enter the lowercase alphabets" );
    } else if(mode == 2){
                strcpy(msg, "please enter the Uppercase alphabets" );
    }else{
        printf( "mode must be 1 or 2 : mode = %d \n", mode );
        return EXIT_FAILURE;
    }

    const int BUFSIZE = 100;
    char buf[BUFSIZE];

    char str[100];

    enum Input in;

    while(1)
    {

        printf("%s \n", msg );
        printf("> ");  // prompt

        // input from keyboard
        in = getInputChars(buf, BUFSIZE);

    int flag = 0;
    switch(in)
    {
        case SUCCESS:
            break;
        case EMPTY:
            flag = 1;
            break;
        case ERROR:
            printf("error \n");
            break;
         case OVER:
            printf("over: %s (%lu) \n", buf, strlen(buf) );
            break;
    }

    // qiut when only return key
    if(flag){
        break;
    }

        if(mode == 1){
            str2upper(buf, str);
        } else if(mode == 2){
            str2lower(buf, str);
        }

       printf("%s \n", str );

    } // while

       printf("quit \n");

    return EXIT_SUCCESS;
}

