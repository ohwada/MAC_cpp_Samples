/**
 * prime.c
 * prime numbers up to 1,000
 * 2022-06-01 K.OHWADA
 */

// gcc prime.c -lgmp  

#include <stdio.h>
#include <gmp.h>


/**
 * main
 */
int main()
{
    mpz_t op;

    mpz_init(op);
   
    int sum = 0;

// prime numbers up to 1,000
    for(int i=2; i<1000; i++)
    {
        mpz_set_ui (op, i);
        int ret = mpz_probab_prime_p(op, 20);
        if(ret == 2) {
            sum ++;
            gmp_printf("%Zd \n", op);
        }
    }// for

    printf("sum=%d \n", sum);
	return 0;
}


// 2 
// 3 
// 5 
// sum=168 


