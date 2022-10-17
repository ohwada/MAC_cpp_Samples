/**
 * get_home.c
 * 2022-06-01 K.OHWADA
 */

// get environment variable HOME

// CmnConf_GetEnv
// https://ityorozu.net/dev/cmn-clib/doc/html/d1/d72/_cmn_conf_8h.html#a1a5e4e55ffb6d008e80e2b10af2001ce

#include <stdio.h>
#include <stdlib.h>
#include "cmnclib/CmnConf.h"

int main()
{

    const size_t BUFSIZE = 128;
    char buf[BUFSIZE];

    const char * 	envName = "HOME";

    int ret = CmnConf_GetEnv(buf, envName);	
    if(!ret){
        fprintf(stderr, "GetEnv faild: %s \n", envName);
    }

    printf("%s : %s \n", envName, buf);

    return 0;
}
