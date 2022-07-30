/**
 * random.c
 * generate 100-bit random numbers
 * 2022-06-01 K.OHWADA
 */

// gcc random.c -lgmp  

// reference : https://qiita.com/ykkhrt/items/ba89fc6e8ef7b76fc401

#include <time.h>
#include <gmp.h>


/**
 * main
 */
int main(int argc, char const *argv[])
{
// initialize multiple-precision integer structure
    mpz_t a;
    mpz_init(a);

// initialize the state structure of the pseudo-random number generator
// the default is Mersenne Twister
    gmp_randstate_t state;
    gmp_randinit_default(state);

// use time for seed
    time_t rtime;
    time(&rtime);
    gmp_randseed_ui(state, rtime);

   // generate 100-bit random numbers
    mpz_urandomb(a, state, 100);

// output in hexadecimal
    gmp_printf("%Zx \n",a);

// clean up
    mpz_clear(a);
    gmp_randclear(state);

    return 0;
}


// 54bbe6c276b7c18028a6702be


