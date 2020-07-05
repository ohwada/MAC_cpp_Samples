/**
 * C++ keyborad sample
 * 2020-03-01 K.OHWADA
 */


// get the event of whether a key was pressed
// reference: https://hotnews8.net/programming/tricky-code/c-code03


#include "keyboard.h"



/**
 * main
 */
int main(void)
{
    printf("quit when press any key \n");

    while (1) {
        if (kbhit()) {
            break;
        }
    }

    int ch = getchar();
    if (iscntrl(ch) == 0) {
            printf("press: '%c' \n", ch);
    }else{
            char *code = getCntrlCode(ch);
            printf("press: %d ( %s ) \n", ch, code);
    }

    return 0;
}
