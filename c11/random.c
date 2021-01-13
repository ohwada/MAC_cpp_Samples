/**
 * C sample
 * 2020-03-01 K.OHWADA
 */


// generate random number using random()
// since C11
// reference : https://www.jpcert.or.jp/sc-rules/c-msc30-c.html
// https://linuxjm.osdn.jp/html/LDP_man-pages/man3/random.3.html

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * main
 */
int main(void)
{

    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
        printf("timespec_get faild \n");
        return 1;
    }

    srandom(ts.tv_nsec ^ ts.tv_sec);

    for(int i=0; i<10; i++)
    {    
        int r = random();
        printf("%d \n", r);
    }

// 1188720232 
// 599176564 

    return EXIT_SUCCESS;
}

