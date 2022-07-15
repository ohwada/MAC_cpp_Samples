/**
 *  callback_func3.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://daeudaeu.com/funcptr/#i-8

#include <stdio.h>


/**
 *  add
 */
int add(int x, int y, int z)
{
    return x + y + z;
}


/**
 *  func
 */
int func(int (*callback)(int, int, int), int x)
{
    return callback(x, x, x);
}


/**
 *  main
 */
int main(void)
{
   int ret;

   ret = func(add, 100);

   printf("ret = %d \n", ret);

   return 0;
}

// ret = 300 
