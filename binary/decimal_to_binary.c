/**
 * decimal_to_binary.c
 * 2022-06-01 K.OHWADA
 */

//  gcc decimal_to_binary.c

#include <stdio.h>
#include "decimal_to_binary.h"


/**
 * main
 */
int main(void)
{
    const int DIGITS = 8;
    const int BINSIZE = DIGITS;
    const int BUFSIZE = DIGITS +1;
    int binary[BINSIZE];
    char buf[BUFSIZE];

    for(int i=0; i<=32; i++)
    {
        decimal_to_binary( binary, BINSIZE, i, DIGITS);
        binary_to_string(buf, BUFSIZE, binary, DIGITS);
        printf("%d: %s : ", i, buf);
       print_binary( binary, DIGITS );
        printf("\n");
    }

  return 0;
}

// 0: 000000000 : 000000000 
// 1: 000000001 : 000000001 
// 2: 000000010 : 000000010 
// 3: 000000011 : 000000011

