/**
 * file_write.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnFile.c

// CmnFile_WriteNew 
// https://ityorozu.net/dev/cmn-clib/doc/html/db/d46/_cmn_file_8h.html#a3d53b0f2703f30eeaeb139a801b7d1f4

// CmnFile_Remove
// https://ityorozu.net/dev/cmn-clib/doc/html/db/d46/_cmn_file_8h.html#aaca48be3591e6457796dc15c70bb81f9

// CmnFile_Exists
// https://ityorozu.net/dev/cmn-clib/doc/html/db/d46/_cmn_file_8h.html#add4fa31cc99ab59b9f827fc44a0d0482

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cmnclib/CmnFile.h"
#include "cmnclib/CmnData.h"


int main()
{	

	char *file = "test/WriteTest.txt";

	char *data = "The quick brown fox jumps over the lazy dog";


//  file write test
	int ret = CmnFile_WriteNew(file, data, strlen(data));
	if (ret != 0) {
		fprintf(stderr, "file write faild: %s \n", file);
	}

	CmnDataBuffer *buf = CmnDataBuffer_Create(0);

// Read written data
	if (CmnFile_ReadAll(file, buf) == NULL) {
		fprintf(stderr, "file read faild: %s \n", file);
	}

		printf("%s \n", buf->data);

	assert(strcmp(buf->data, data) == 0);

// buffer release
	CmnDataBuffer_Free(buf);

// remov file
	CmnFile_Remove(file);

	if (CmnFile_Exists(file)) {
		fprintf(stderr, "cannot remove file: %s \n", file);
	}


	printf("successful \n");

	return 0;
}
