/**
 * recursion sample
 * 2020-07-01 K.OHWADA
 */

// Example: Sum of Natural Numbers Using Recursion
// f(n) = n + f(n-1)
// reference : https://www.programiz.com/c-programming/c-recursion


#include <stdio.h>
#include <stdlib.h>

// prototype
int sum(int n);

/**
 * main
 */
int main(void) 
{
    int number, result;

    printf("Enter a positive integer: ");
    scanf("%d", &number);

    result = sum(number);

    printf("sum = %d \n", result);

    return EXIT_SUCCESS;
}


/**
 * sum
 */
int sum(int n) {
    if (n != 0)
        // sum() function calls itself
        return n + sum(n-1); 
    else
        return n;
}

