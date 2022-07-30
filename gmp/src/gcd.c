/**
 * gcd.c
 * Greatest Common divisor
 * 2022-06-01 K.OHWADA
 */

// gcc gcd.c -lgmp  


#include <gmp.h>


/**
 * main
 */
int main()
{
    mpz_t a, b, c;

    mpz_init(a);
    mpz_init(b);
    mpz_init(c);
    mpz_set_ui (a, 8633);
    mpz_set_ui (b, 6052);

	mpz_gcd (c, a, b);

    gmp_printf("gcd(%Zd, %Zd)=%Zd \n", a, b, c);

	return 0;
}


// gcd(8633, 6052)=89 


