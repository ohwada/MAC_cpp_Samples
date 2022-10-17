/**
 * log_write.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnLog.c 

//	CmnLogEx_Create 
// https://ityorozu.net/dev/cmn-clib/doc/html/d4/db8/_cmn_log_8h.html#a0cf143f651c16c8fbf489234f37e9346


// CmnLogEx_Put 
// https://ityorozu.net/dev/cmn-clib/doc/html/d4/db8/_cmn_log_8h.html#aa47f47b3347fe0ef90587a3f23ced831

#include <stdio.h>
#include <stdlib.h>

#include "cmnclib/CmnLog.h"

int main()
{
    char *file = "log/test.log";

	CmnLogEx* logex = CmnLogEx_Create(file, CMN_LOG_LEVEL_DEBUG, NULL);

	CmnLogEx_Put(logex, CMN_LOG_LEVEL_DEBUG, "test[%s] val[%s]", "AAA", "BBB");

	printf("saved: %s \n", file);

    return 0;
}

// saved: log/test.log 
