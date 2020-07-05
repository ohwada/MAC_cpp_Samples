/**
 * ConsoleUtil Sample
 * 2020-03-01 K.OHWADA
 */

// progress roting
// display the following characters in the same line, as rotating 
// '-', '\', '|', '/'

// reference : https://www.mm2d.net/main/prog/c/console-04.html

#include <stdio.h>
#include <unistd.h>


/**
 * progress
 */
void progress() {
  static int pos = 0;
  static char mark[] = {'-','\\','|','/'};
  fprintf(stderr, "\r%c", mark[pos]);
  pos = (pos + 1) % sizeof(mark);
}


/**
 * main
 */
int main(int argc, char**argv) {

  for (int i = 0; i < 100; i++) {
    progress();
    usleep(100000);
  } // for

  fprintf(stderr, "\n finish! \n");
  return 0;
}
