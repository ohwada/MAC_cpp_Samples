/**
 * thread.c
 * 2022-06-01 K.OHWADA
 */


// run another

// refrence : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnThread.c

// CmnThread_Init 
// https://ityorozu.net/dev/cmn-clib/doc/html/db/d90/_cmn_thread_8h.html#a8908c4032c0fc4a715c7ea56145dc6d1

// CmnThread_Start 
// https://ityorozu.net/dev/cmn-clib/doc/html/db/d90/_cmn_thread_8h.html#a1537584289d589051c69be42c06091a8

// CmnThread_Join 
// https://ityorozu.net/dev/cmn-clib/doc/html/db/d90/_cmn_thread_8h.html#aa485415b8cd44fdfe6f0b8a96501fe23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cmnclib/CmnThread.h"

const int COUNT = 1230000;


static void methodNormal(CmnThread *thread)
{


	int *dat = thread->data;

	for (int i=0; i <  COUNT; i++) {
		(*dat)++;
	} // for

}


int main()
{
	const int INIT = 456;

	CmnThread thread;
	int data = INIT;

	CmnThread_Init(&thread, methodNormal, &data, NULL);
	CmnThread_Start(&thread);
	CmnThread_Join(&thread);

	printf("%d \n", data);

	assert(data ==  (COUNT+INIT) );

    return 0;
}

// 1230456
