/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// read and write text file 
// test for text_file.h

#include <stdio.h>
#include "file_util.h"
 
/**
 * main
 */
int main(int argc, char** argv)
{ 

    char* input = "data/sample.txt";
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
         return 1;
    }  

    printf("---------- \n");
    printf("%s \n", data);
    printf("---------- \n");

    int ret = file_text_write(output, data, error);
    if (ret != 0){ 
       printf("error %s: %s \n", error, output );
        return 1;
    } 

    printf("write to: %s \n", output);

    return 0;
}


// ----------
// Mac
// ...
// ----------
// write to: sample_out.txt

