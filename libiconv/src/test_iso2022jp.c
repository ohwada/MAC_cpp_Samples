/**
 * iconv Sample
 * 2021-02-01 K.OHWADA
 */

// convert codeset ISO2022_JP to UTF-8
// C version

// gcc test_iso2022jp.c `pkg-config --cflags --libs iconv` 


#include <stdio.h>
#include <stdlib.h>
#include "iso2022jp.h"
#include "./samples/sample_enc.h"


/*
 * main
 */
int main(void)
{

    char *expect_utf8 = (char *)EXPECT_UTF8;

    printf("expect: %s \n", expect_utf8);

    char buf1[CONV_BUFSIZE];
    char buf2[CONV_BUFSIZE];
    char error[CONV_ERROR_SIZE];

    bool ret1 = iso2022jp_to_utf8( 
    (char *)ISO2022JP,  
    SAMPLE_ISO2022JP_SIZE, 
    (char *)buf1, 
    CONV_BUFSIZE, 
    (char *)error );

    if(ret1){
        printf("conv: %s \n", buf1);
    } else {
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }

    if( strcmp( expect_utf8, buf1 ) == 0 ) {
        printf(" iso2022jp_to_utf8 successful \n");
    } else{
        fprintf(stderr, " iso2022jp_to_utf8 faild \n");
        return EXIT_FAILURE;
    }

   
    bool ret2 = utf8_to_iso2022jp( 
    (char *)EXPECT_UTF8,  
    SAMPLE_UTF8_SIZE, 
    (char *)buf2, 
    CONV_BUFSIZE, 
    (char *)error );

    if(!ret2){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }


   printf("expect: ");
    dump_chars( (char *)ISO2022JP, SAMPLE_ISO2022JP_SIZE );
    printf("conv: ");
    dump_string(buf2);

    bool ret3 = cmp_chars( (char *)ISO2022JP, 
    (char *)buf2,  SAMPLE_ISO2022JP_SIZE );

    if (ret3) {
        printf("utf8_to_iso2022jp successful \n");
    } else{
        fprintf(stderr, "utf8_to_iso2022jp faild \n");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

