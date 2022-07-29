/**
 * bool.c
 * 2022-06-01 K.OHWADA
 */

// gcc bool.c
// reference : https://www.buildinsider.net/language/clang/01

#include <stdio.h>
#include <stdbool.h>
 

/**
 * isoctal
 */
bool isoctal(char c) {
  return '0' <= c && c < '8';
}
 

/**
 * main
 */
int main(int argc, char **argv) 
{
  char c = '3';
  if (isoctal(c)) {
    printf("%c is octal \n", c);
  }
    return 0;
}

 // 3 is octal 
