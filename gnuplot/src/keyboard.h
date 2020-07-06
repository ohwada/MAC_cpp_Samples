/**
 * keyboard
 * 2020-03-01 K.OHWADA
 */


#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>


#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define KEY_TAB 9
#define KEY_LF 10
#define KEY_ESC 27

int kbhit(void);

int getKey(void);

char* getCntrlCode(int ch);

void waitPressESC(void);

char* get_password_without_echo(void);

char* get_password_with_echo_star(void);

#endif /* KEYBOARD_H */

