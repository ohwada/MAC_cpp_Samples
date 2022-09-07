/**
 * test_read_write_binary.c 
 * 2020-02-01 K.OHWADA
 */

// test for file_util.h

// gcc test_read_write_binary.c -o bin/binary

#include <stdio.h>
#include "file_util.h"
 

/**
 * main
 */
int main(int argc, char** argv)
{ 

    char* input = "../data/baboon.png";
    char* output = "baboon_out.png";

    if(argc == 3) {
        input = argv[1];
        output = argv[2];
    } else {
        printf("Usage: %s  <Input filename> <Output filename> \n", argv[0] );
    }

    size_t size;
    char error[100];
    uint8_t *data = file_binary_read(input, &size, (char *)error);
    if (!data){ 
        printf("%s: %s \n", error, input );
        return EXIT_FAILURE;
    }  

    printf("size : %zu \n", size);
    dump_binary(data, 100);

    bool ret = file_binary_write(output, data, size, (char *)error);
    if ( !ret ){ 
       printf("%s: %s \n", error, output );
        return EXIT_FAILURE;;
    } 

    printf("write to: %s \n", output);

    return EXIT_SUCCESS;
}


// write to: baboon_out.png 


