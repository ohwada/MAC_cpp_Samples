/**
 * C++ Keyborad Sample
 * 2020-03-01 K.OHWADA
 */

// enter password with echo star '*'
// reference : https://www.mm2d.net/main/prog/c/console-05.html


#include "keyboard.h"


/**
 * main
 */
int main(int argc, char **argv) 
{

    printf("enter password \n > ");
    char *passwd = get_password_with_echo_star(); 
    printf("\n password: %s \n", passwd );

  return 0;
}
