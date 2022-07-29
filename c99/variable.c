/**
 * variable.c
 * variable declarations
 * 2022-06-01 K.OHWADA
 */

/*
 * reference : https://www.buildinsider.net/language/clang/01
 */

#include <stdio.h>
#include <assert.h>
 

/**
 * sum
 */
int sum(int count, int a[]) 
{
  assert(count >= 0);

//
 /* error in ANSI-C */
  int sum = 0;

 /* error in ANSI-C */
  for (int i = 0; i < count; ++i) {
    sum += a[i];
  } 

  return sum;
}


 /**
 * main
 */
int main(int argc, char **argv) 
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int count = sizeof(data) / sizeof(data[0]);
    printf("sum = %d \n", sum( count, data) );
	return 0;
}

/*
 * sum = 45 
*/

