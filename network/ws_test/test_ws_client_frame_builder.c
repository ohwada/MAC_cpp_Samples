/**
 * test_ws_client_frame_builder.c
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../ws_client/ws_client_frame_builder.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    char *text = "Hello, world!"; 

    int close_code = CLOSE_NORMAL;

    size_t expect_size1 = strlen(text) + 6;

    size_t expect_size2 = 8;

    char expect1[] = { (char)0x81, (char)0x8d };

    char expect2[] = {(char)0x88, (char)0x82 };


// build text
{
    printf("build text: %s \n", text);
 
    char data1[100];
    
    size_t data_size;

    build_client_text(text, (char*)data1, &data_size);

     dump_frame_data( data1, data_size);

    assert(data_size == expect_size1);

    assert( memcmp(data1, expect1, 2) == 0 );

}

// build close
{
    printf( "\n build close: %d \n", close_code);

    char data2[100];
    
    size_t data_size;

    build_client_close( close_code, "", data2, &data_size );

    dump_frame_data(data2, data_size);

    assert(data_size == expect_size2);

    assert( memcmp(data2, expect2, 2) == 0 );

}

    printf("\n successful \n");

    return 0;
}

