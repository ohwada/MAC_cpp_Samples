/**
 * time_now.c
 * 2022-06-01 K.OHWADA
 */

// Display current date and time

// refrence : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnTime.c

// CmnTimeDateTime_SetNow 
// https://ityorozu.net/dev/cmn-clib/doc/html/dd/dd5/_cmn_time_8h.html#a09d2f0089ca0022ad1f9095babe7017b

//	CmnTimeDateTime_ToString 
// https://ityorozu.net/dev/cmn-clib/doc/html/dd/dd5/_cmn_time_8h.html#a4174a0d3aa0cba7a343c2f22adc5f3c7

// CmnTime_Format 
// https://ityorozu.net/dev/cmn-clib/doc/html/dd/dd5/_cmn_time_8h.html#afb2a2a06b8bd3d433d3b642c61007250


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cmnclib/CmnTime.h"

int main()
{

	CmnTimeDateTime datetime;
	CmnTimeDateTime_SetNow(&datetime);

	char buf1[CMN_TIME_DATETIME_STRING_BUFFER_SIZE];

CmnTimeDateTime_ToString	(&datetime,buf1 );	

printf("1: %s \n", buf1);	

	char buf2[CMN_TIME_FORMAT_SIZE_ALL];

 	CmnTime_Format(&datetime,
CMN_TIME_FORMAT_ALL, buf2 );

printf("2: %s \n", buf2);	

    return 0;
}


// 2022/10/15 16:55:08 
