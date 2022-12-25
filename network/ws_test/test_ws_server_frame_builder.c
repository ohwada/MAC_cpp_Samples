/**
 * test_ws_server_frame_builder.c
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../ws_server/ws_server_frame_builder.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    char *text = "Hello, world!"; 

    int close_code = CLOSE_NORMAL;

    char expect1[] = { (char)0x81, 0x0d, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21};

       char expect2[] = { (char)0x88, 0x02, 0x03, (char)0xe8 };


// build text
{
    printf("build text: %s \n", text);
 
    char data1[100];
    
    size_t data_size;

    build_server_text(text, (char*)data1, &data_size);

     dump_frame_data( data1, data_size);

    assert( memcmp(data1, expect1, data_size) == 0);
}

// build close
{
    printf( "\n build close: %d \n", close_code);

    char data2[100];
    
    size_t data_size;

    build_server_close( close_code, "", data2, &data_size );

    dump_frame_data(data2, data_size);

    assert( memcmp(data2, expect2, data_size) == 0);
}

    printf("\n successful \n");

    return 0;
}

