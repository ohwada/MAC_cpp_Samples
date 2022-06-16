/*
 * version.c
 * display version
 * 2022-0501 K.OHWADA 
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


/**
 * main
 */
int main() 
{
    printf("VERSION: %s\n", NCURSES_VERSION);
    printf("version: %s\n", curses_version());
    return 0;
}

// VERSION: 6.3
// version: ncurses 6.3.20211021

