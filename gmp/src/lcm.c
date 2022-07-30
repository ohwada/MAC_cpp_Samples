/**
 * lcm.c
 * Least Common Multiple  
 * 2022-06-01 K.OHWADA
 */

// gcc lcm.c -lgmp  


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
    mpz_set_ui (a, 225);
    mpz_set_ui (b, 365);

	mpz_lcm(c, a, b);

    gmp_printf("lcm(%Zd, %Zd)=%Zd \n", a, b, c);

	return 0;
}

// lcm(225, 365)=16425 


