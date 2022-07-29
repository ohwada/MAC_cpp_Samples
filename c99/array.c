/**
 * array.c
* variable length array 
 * 2022-06-01 K.OHWADA
 */

// gcc array.c
// reference : https://www.buildinsider.net/language/clang/01

#include <stdio.h>
 

/**
 * fsize3
 */
size_t fsize3(int n) {
  char b[n + 3];
  return sizeof b;
}
 

/**
 * main
 */
int main(int argc, char **argv) 
{
  printf("size: %ld \n", fsize3(10));
	return 0;
}
 
// size: 13 
