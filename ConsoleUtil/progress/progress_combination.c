/**
 * ConsoleUtil Sample
 * 2020-03-01 K.OHWADA
 */

// progress combination
// display  progress bar and counter as below 
// 0%       50%       100% 
//+---------+---------+ 
//###### 
// 50% 

// escape sequence
// ESC[2A : move up the cursor two lines

// reference : https://www.mm2d.net/main/prog/c/console-04.html

#include <stdio.h>
#include <unistd.h>


/**
 * main
 */
int main(int argc, char**argv) 
{
  int i, j;

  fprintf(stderr, "0%%       50%%       100%%\n");
  fprintf(stderr, "+---------+---------+\n");

  for (i = 0; i <= 100; i++) {
    for (j = 0; j < i / 5 + 1; j++) {
      fprintf(stderr, "#");
    } // for j
    fprintf(stderr, "\n");
    fprintf(stderr, "%3d%% \n", i);
    usleep(100000);
    fprintf(stderr, "\033[2A");
  } // for i

  fprintf(stderr, "\n \n finish! \n");
  return 0;
}
