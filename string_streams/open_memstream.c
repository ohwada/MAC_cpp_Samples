/**
 * string streams
 * 2021-02-01 K.OHWADA
 */

// open a dynamic memory buffer
// sample code for open_memstream
// https://man7.org/linux/man-pages/man3/open_memstream.3.html

// gcc open_memstream.c


// https://www.gnu.org/software/libc/manual/html_node/String-Streams.html

#include <stdio.h>


/**
 * main
 */

int main (void)
{
  char *bp;
  size_t size;
  FILE *stream;

  stream = open_memstream(&bp, &size);
  fprintf (stream, "hello");
  fflush (stream);
  printf ("buf = `%s', size = %zu \n", bp, size);

// will be added
  fprintf (stream, ", world");
  fclose (stream);
  printf ("buf = `%s', size = %zu \n", bp, size);

  return 0;
}


// buf = `hello', size = 5 
// buf = `hello, world', size = 12 

