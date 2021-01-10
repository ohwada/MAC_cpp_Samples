/**
 * recursion sample
 * 2020-07-01 K.OHWADA
 */

// C Program to Find Factorial of a Number Using Recursion
// f(n) = n * f(n -1)
// reference  https://www.programiz.com/c-programming/examples/factorial-recursion

#include<stdio.h>
#include<stdlib.h>

// prototype
long int multiplyNumbers(int n);


/**
 * main
 */
int main(void) 
{
    int n;
    printf("Enter a positive integer: ");
    scanf("%d",&n);
    printf("Factorial of %d = %ld  \n", n, multiplyNumbers(n) );

     return EXIT_SUCCESS;
}


/**
 * multiplyNumbers
 */
long int multiplyNumbers(int n) {
    if (n>=1)
        return n*multiplyNumbers(n-1);
    else
        return 1;
}
