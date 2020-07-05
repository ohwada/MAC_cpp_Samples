/**
 * C++ keyborad sample
 * 2020-03-01 K.OHWADA
 */


// wait press ESC key


#include "keyboard.h"



/**
 * main
 */
int main(void)
{
    printf("quit when press ESC key \n");

    waitPressESC();

    printf("quit \n");
    return 0;
}
