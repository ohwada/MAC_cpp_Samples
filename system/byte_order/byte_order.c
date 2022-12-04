/**
 * byte_order.c
 * 2022-06-01 K.OHWADA
 */

// Network byte order
// http://cms.phys.s.u-tokyo.ac.jp/~naoki/CIPINTRO/NETWORK/endian.html

#include <stdio.h>


/**
 * main
 */
int main()
{
    unsigned int x = 0x7f000001;
    printf("%08x \n", x);

    unsigned char* ptr = (unsigned char*) &x;
    printf("%02x,%02x,%02x,%02x\n", ptr[0], ptr[1], ptr[2], ptr[3] );

    return 0;
}


// 7f000001 
// little endian (INtel CPU)
// 01,00,00,7f

// big endian
// 7f,00,00,01


