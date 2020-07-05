/**
 * C++ progress sample
 * 2020-03-01 K.OHWADA
 */

// progress bar
// increment characters one by one on the same line like bar

// reference : https://www.mm2d.net/main/prog/c/console-04.html

#include <stdio.h>
#include <unistd.h>


/**
 * main
 */
int main(int argc, char**argv) {
  int i;

  for (i = 0; i < 20; i++) {
    fprintf(stderr, "#");
    usleep(500000);
  } // for

  fprintf(stderr, "\n finish! \n");
  return 0;
}
