/**
 * test_bin_hex.h
 * 2022-06-01 K.OHWADA
 */ 

// reference : https://qiita.com/AsladaGSX/items/e08274e28eec8498d964

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hex.h"


/**
 * main
 */ 
int main()
{

   const char * hexPriv = "b91c37cd87a0a66fd0c22eeac1bbac277db47f792310e3a9bb3ebd220fa72a59";

    const char * hexOdd = "b91c37cd87a0a66fd0c22eeac1bbac277db47f792310e3a9bb3ebd220fa72a59F";

    const char * hexPub = "04daa7c6653f3e1ef969550c1018a1dd2d534d5169f155a8583d79abac1aca9e0d93cdc2a6f8368cf6d703f96dfd7cdb0b3aee8514d8c0225f8732dae79f487578";

    const unsigned char binPriv[] = { 0xb9, 0x1c, 0x37, 0xcd, 0x87, 0xa0, 0xa6, 0x6f, 0xd0, 0xc2, 0x2e, 0xea, 0xc1, 0xbb, 0xac, 0x27, 0x7d, 0xb4, 0x7f, 0x79, 0x23, 0x10, 0xe3, 0xa9, 0xbb, 0x3e, 0xbd, 0x22, 0x0f, 0xa7, 0x2a, 0x59, };
    
const unsigned char binPub[] = { 0x04, 0xda, 0xa7, 0xc6, 0x65, 0x3f, 0x3e, 0x1e, 0xf9, 0x69, 0x55, 0x0c, 0x10, 0x18, 0xa1, 0xdd, 0x2d, 0x53, 0x4d, 0x51, 0x69, 0xf1, 0x55, 0xa8, 0x58, 0x3d, 0x79, 0xab, 0xac, 0x1a, 0xca, 0x9e, 0x0d, 0x93, 0xcd, 0xc2, 0xa6, 0xf8, 0x36, 0x8c, 0xf6, 0xd7, 0x03, 0xf9, 0x6d, 0xfd, 0x7c, 0xdb, 0x0b, 0x3a, 0xee, 0x85, 0x14, 0xd8, 0xc0, 0x22, 0x5f, 0x87, 0x32, 0xda, 0xe7, 0x9f, 0x48, 0x75, 0x78, };


printf("bin2hex \n");

char* hex1 = bin2hex( (char *)binPriv, sizeof(binPriv));
// printf("%s \n", hex1);

char* hex2 = bin2hex( (char *)binPub, sizeof(binPub));
// printf("%s \n", hex2);

    assert( strcmp(hex1,  hexPriv) == 0);
    assert( strcmp(hex2,  hexPub) == 0);

    free(hex1);
    free(hex2);

    printf("hex2bin \n");

    size_t binsize1 = calc_binsize( (char *)hexPriv);
    size_t binsize2 = calc_binsize((char *)hexPub);
    size_t binsize3 = calc_binsize((char *)hexOdd);

    char buf1[binsize1];
    char buf2[binsize2];
    char buf3[binsize3];

    hex2bin(hexPriv, buf1, binsize1);

    assert(memcmp(buf1, binPriv, sizeof(binPriv)) == 0);

    hex2bin(hexPub, buf2, binsize2);

    assert(memcmp(buf2, binPub, sizeof(binPub)) == 0);

// the last character is not converted
 // when the hex string is odd
    hex2bin(hexOdd, buf3, binsize3);

    dump_bin(buf3, binsize3);

    assert(memcmp(buf3, binPriv, sizeof(binPriv)) == 0);

    printf("sucessful \n");

    return 0;
}

// bin2hex 
// hex2bin 
// sucessful 
