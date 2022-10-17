/**
 * file_read.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnFile.c

 // CmnFile_ReadAllText
// https://ityorozu.net/dev/cmn-clib/doc/html/db/d46/_cmn_file_8h.html#a4d17319d18eff9ebe4aa31462ac0be62

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cmnclib/CmnFile.h"
#include "cmnclib/CmnData.h"

int main()
{
    const size_t BUFSIZE = 128;
    char tmp1[BUFSIZE];
    char tmp2[BUFSIZE];

    char* file = "res/ReadAll.txt";

	CmnDataBuffer *buffer = CmnDataBuffer_Create(0);
	CmnDataBuffer *buffer2 = CmnFile_ReadAll(file, buffer);

    if(buffer2 == NULL){
        fprintf(stderr, "ReadAll failed \n");
    }

    printf("%s \n", buffer->data);

    size_t len = strlen(buffer->data);
    printf("\n length: %zu \n",  len);

    char* start =  strncpy(tmp1,  buffer->data, 5);
    printf("%s \n", start);

    char* end =  strncpy(tmp2,  (char*)(buffer->data + buffer->size - 3), 3);
    printf("%s \n", end);

    assert(len == 4959);

    assert( strcmp(start,  "START") == 0);

    assert( strcmp(end,  "END") == 0);

	printf("successful \n");

    return 0;
}


// START
// 11111111112222222222333333333344444444445555555555666666666677777777778888888888999999999900000000

