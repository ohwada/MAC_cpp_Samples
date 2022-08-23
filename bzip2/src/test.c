/**
 *  test.c
 * 2022-06-01 K.OHWADA
 */

// minimal code to check if bzip2 was installed correctly
// reference : https://www.s-yata.jp/docs/libbzip2/

#include <stdio.h>
#include <bzlib.h>


/**
 *  main
 */
int main(void) 
{
  bz_stream strm = { .bzalloc = NULL, .bzfree = NULL, .opaque = NULL };
  BZ2_bzCompressInit(&strm, 9, 0, 0);
  BZ2_bzCompressEnd(&strm);

printf("successful \n");

  return 0;
}

