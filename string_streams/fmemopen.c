/**
 * string streams
 * 2021-02-01 K.OHWADA
 */

// open memory as stream
// sample code for fmemopen
// https://man7.org/linux/man-pages/man3/fmemopen.3.html

// gcc fmemopen.c

// reference : https://www.gnu.org/software/libc/manual/html_node/String-Streams.html

#include <stdio.h>
#include <string.h>

static char buffer[] = "foobar";


/**
 * main
 */
int main(void)
{
  int ch;
  FILE *stream;

printf ("buffer: %s \n", buffer);

  stream = fmemopen(buffer, strlen (buffer), "r");
    while ((ch = fgetc (stream)) != EOF) {
        printf ("Got %c \n", ch);
    }

    fclose (stream);

    return 0;
}


// buffer: foobar 
// Got f
// Got o
// Got o
// Got b
// Got a
// Got r


