// 2022-0501 K.OHWADA 

// version.c
// display version

//　gcc version.c -o version  `pkg-config --cflags --libs ncurses`

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

