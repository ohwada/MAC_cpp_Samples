/**
 * test_read_write_text.c
 * 2020-02-01 K.OHWADA
 */

// read and write text file 
// test for text_file.h

// gcc test_read_write_text.c -o bin/text

#include <stdio.h>
#include "file_util.h"
 
/**
 * main
 */
int main(int argc, char** argv)
{ 

    char* input = "sample.txt";
    char* output = "sample_out.txt";

    if(argc == 3) {
        input = argv[1];
        output = argv[2];
    } else {
        printf("Usage: %s  <Input filename> <Output filename> \n", argv[0] );
    }

    char error[100];
    char* data = file_text_read(input, (char *)error);
    if (!data){ 
        printf("error %s: %s \n", error, input );
        return EXIT_FAILURE;
    }  

    printf("---------- \n");
    printf("%s \n", data);
    printf("---------- \n");

    bool ret = file_text_write(output, data, error);
    if ( !ret ){ 
       printf("error %s: %s \n", error, output );
                return EXIT_FAILURE;;
    } 

    printf("write to: %s \n", output);

    return EXIT_SUCCESS;;
}


// ----------
// Mac
// ...
// ----------
// write to: sample_out.txt

