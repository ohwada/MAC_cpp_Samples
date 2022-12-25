/**
 * test_ws_frame_parser.c
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../ws_server/ws_frame_parser.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

  char data1[] = { (char)0x81, (char)0x8d, (char)0xb6, 0x36, (char)0xa1, (char)0xed, (char)0xfe, (char)0x53, (char)0xcd, (char)0x81, (char)0xd9, (char)0x1a, (char)0x81, (char)0x9a, (char)0xd9, 0x44, (char)0xcd, (char)0x89, (char)0x97};

 char data2[] = { (char)0x81, (char)0x0d, (char)0x48, (char)0x65, (char)0x6c, (char)0x6c, (char)0x6f, (char)0x2c, 0x20, (char)0x77, (char)0x6f, (char)0x72, (char)0x6c, (char)0x64, (char)0x21};

char data3[] = {(char)0x88, (char)0x82, (char)0x67, (char)0x3a, (char)0x0f, (char)0x22, (char)0x64, (char)0xd2};

char data4[] = { (char)0x88, (char)0x02, (char)0x03, (char)0xe8 };

    char *expect = "Hello, world!"; 

    int expect_code = 1000;



// data1
{
    printf("\n data1 \n");

    char text1[100];

    parse_text( (char *)data1, sizeof(data1), (char *)text1);

    printf( "text1: %s \n", text1);

    assert(strcmp(text1, expect)==0);
}

// data2
{
    printf("\n data2\n");

    char text2[100];

    parse_text( (char *)data2, sizeof(data2), (char *)text2);

    printf("text2: %s \n", text2);

    assert(strcmp(text2, expect)==0);
}

// data3
{
    printf("\n data3 \n");

    int closecode3;
    char reason3[100];

    parse_close( (char *)data3, sizeof(data3), &closecode3, reason3);

    printf("close code3: %d \n", closecode3);

    assert(closecode3 == expect_code);
}

// data4
{
    printf("\n data4 \n");

    int closecode4;
    char reason4[100];

    parse_close( (char *)data4, sizeof(data4), &closecode4, reason4);

    printf("close code4: %d \n", closecode4);

    assert(closecode4 == expect_code);
}

    printf("\n successful \n");

    return 0;
}

