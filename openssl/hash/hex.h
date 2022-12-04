#pragma once
/**
 * hex.h
 * 2022-06-01 K.OHWADA
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// prototype
char* bin2hex(char* bin, size_t size);
void hex2bin(const char *hex, char *bin, size_t binsize);
size_t calc_binsize(char* hex);
void dump_bin(char* bin, size_t size);


/**
 * bin2hex
 */ 
// reference : https://daeudaeu.com/c-hexdump/
char* bin2hex(char* bin, size_t size)
{
    const char NUL = '\0';

    size_t BUFSIZE = 3;
    char buf[BUFSIZE];

    char* res = (char *)calloc(sizeof(char *), (2*size+1) );
    res[0] = NUL;

    for(int i=0; i<size; i++)
    {
        memset(buf, NUL, BUFSIZE);
        snprintf(buf, BUFSIZE, "%02x", (unsigned char)bin[i] );
        strcat(res, buf);
    } // for

     return res;
}


/**
 * hex2bin
 */
// the last character is not converted
 // when the hex string is odd
// reference : https://qiita.com/AsladaGSX/items/e08274e28eec8498d964
void hex2bin(const char *hex, char *bin, size_t binsize) 
{

    for (; binsize && isxdigit(hex[0]) && isxdigit(hex[1]); hex += 2, bin += 1, binsize -= 1) {
            int r = sscanf(hex, "%2hhx", bin);
            if (r != 1) {
                break;
            }
    } // for

}


/**
 * calc_binsize
 */ 
size_t calc_binsize(char* hex)
{
    size_t len =strlen(hex);
    return len/2;
}


/**
 * dump_bin
 */ 
void dump_bin(char* bin, size_t size)
{
    for(int i=0; i<size; i++){
        printf("%02x, ", (unsigned char)bin[i] );
    }
    printf("\n");
}
