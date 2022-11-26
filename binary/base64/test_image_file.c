/**
 *  test_image_file.c
 * 2022-06-01 K.OHWADA
 */ 


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "base64.h"
#include "file_util.h"


/**
 *  main
 */
int main(void) 
{

    const size_t BUFSIZE = 128;
   char cmd[BUFSIZE];
   char error[BUFSIZE];

    char *file_in = "images/sample.png";
    char *file_out = "out/sample.png";

    size_t data_size;

    char* data = file_binary_read( (char *)file_in, &data_size, (char *) error);

    if( !data || (data_size == 0) ){
        fprintf(stderr, " file_binary_read: %s \n", error);
    }

    printf("data size: %zu \n", data_size);

    char* b64 = base64Encode( (char *)data, data_size, BASE64_TYPE_STANDARD);

    printf("b64 len: %zu \n", strlen(b64) );

    size_t binsize;

    char* bin = base64Decode( b64, &binsize, BASE64_TYPE_STANDARD);

    printf("binsize: %zu \n", binsize );

    bool ret = file_binary_write( (char *)file_out,  bin, binsize, (char *)error);

    if(!ret){
        fprintf(stderr, " file_binary_write: %s \n", error);
    }

    free(data);
    free(b64);
    free(bin);

    char* FORMAT = "cmp %s %s";

    snprintf(cmd, BUFSIZE, (char *)FORMAT, file_in, file_out);

    printf("cmd: %s \n", cmd);

    int res = system(cmd);

    printf("res: %d \n", WEXITSTATUS(res) );

    assert( WEXITSTATUS(res) == 1);

    printf("successful \n");

    return 0;
}
