/**
 * C++ progress sample
 * 2020-03-01 K.OHWADA
 */

// progress counter
// the number will count up in the same line

// escape sequence
// "\r" : return the cursor to the beginning

// reference : https://www.mm2d.net/main/prog/c/console-01.html

#include <stdio.h>
#include <unistd.h>


/**
 * main
 */
int main(int argc, char**argv) 
{
  int i;
  for (i = 0; i <= 100; i++) {
        fprintf(stderr, "\r[%3d / 100]", i);
        usleep(100000);
  } // for

    fprintf(stderr, "\n finish! \n");
    return 0;
}
