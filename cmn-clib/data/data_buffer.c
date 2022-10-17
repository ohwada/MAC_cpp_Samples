/**
 * data_buffer.c
 * 2022-06-01 K.OHWADA
 */


// variable length data buffer

// reference : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnData.c

// CmnDataBuffer_Create	(
// https://ityorozu.net/dev/cmn-clib/doc/html/d1/d74/_cmn_data_8h.html#a7ac03a65abc297b27b7401c91f8ff435

//  	CmnDataBuffer_Append
// https://ityorozu.net/dev/cmn-clib/doc/html/d1/d74/_cmn_data_8h.html#a997926e73b23a26927362465a5335343

// CmnDataBuffer_Free
// https://ityorozu.net/dev/cmn-clib/doc/html/d1/d74/_cmn_data_8h.html#a8812403c659534183d912b9f0188eafa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cmnclib/CmnData.h"

int main()
{
const char NUL = '\0';
const char CHAR_A = 'A';

	const size_t BUFSIZE = 100;
	char data[BUFSIZE+1];

	memset(data, CHAR_A, BUFSIZE);
	data[BUFSIZE] = NUL;
	size_t len = strlen(data);
	printf("len: %zu \n", len);

	CmnDataBuffer *buffer = CmnDataBuffer_Create(2*BUFSIZE);

	for (int i = 0; i < 100; i++) {
		CmnDataBuffer_Append(buffer, data, len);
		printf("%d: %zu, %zu \n", i,  strlen(buffer->data), buffer->bufSize);
	} // for

	assert(strlen(buffer->data) ==  10000);

	assert(buffer->bufSize == 12288);

	CmnDataBuffer_Free(buffer);

	printf("successful \n");

	return 0;
}

// 0: 100, 200 
//  1: 200, 200 
// 2: 300, 300

