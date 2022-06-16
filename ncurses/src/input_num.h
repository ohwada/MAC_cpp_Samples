#pragma once
/**
 * iput_num.h
 *
 * single header library
 * pseudo-implement the echo of character input 
 * and input a numerical value
 * only positive numbers
 *
 * 2020-05-01 K.OHWADA
 */


#ifndef  INPUT_NUM_H
#define INPUT_NUM_H

void init_input_num();
int input_num(int ch);


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>


const char KEY_1 = '1';
const char KEY_2 = '2';
const char KEY_3 = '3';
const char KEY_4 = '4';
const char KEY_5 = '5';
const char KEY_6 = '6';
const char KEY_7 = '7';
const char KEY_8 = '8';
const char KEY_9 = '9';
const char KEY_0 = '0';
const char KEY_LF = '\n';
const char  ZERO = '\0';


// global variable is cleared to zero
const int BUFSIZE = 128;
static char buf[BUFSIZE];


/**
 * init_input_num
 */
void init_input_num()
{
// global variable is cleared to zero, just in case
    buf[0] = ZERO;
}


/**
 * input_num
 */
int input_num(int ch)
{

    if ( ( ch == KEY_1)||(ch == KEY_2)| (ch == KEY_3)|| (ch == KEY_4)|| (ch == KEY_5)|| (ch == KEY_6)|| (ch == KEY_7)|| (ch == KEY_8)|| (ch == KEY_9)|| (ch == KEY_0) ) {
        addch(ch);
        int len = strlen(buf);
        if  (len+1 < BUFSIZE ) {
            buf[ len ] = ch;
            buf[ len + 1] =  ZERO;
        }

    }

    if( ch == KEY_LF ) {
        int len = strlen(buf);
        if(len == 0){
            return -1;
        }
        int num = atoi(buf);
        buf[0] =  ZERO;
        return num;;
    }

    return -1;
}

#endif 
