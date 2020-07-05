/**
 * C++ keyborad sample
 * 2020-03-01 K.OHWADA
 */

// get typed key code
// display typed key character
// reference: https://hotnews8.net/programming/tricky-code/c-code03


#include "keyboard.h"



/**
 * main
 */
int main(void)
{
    printf("quit when press any key \n");

    int key;
    while (1) {
        key = getKey();
        if (key != 0) {
            break;
        }
    }

    if (iscntrl(key) == 0) {
            printf("press: '%c' \n", key);
    }else{
            char *code = getCntrlCode(key);
            printf("press: %d ( %s ) \n", key, code);
    }

    return 0;
}
