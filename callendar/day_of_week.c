/**
 * day_of_week.c
 * 2022-06-01 K.OHWADA
 */

// gcc day_of_week.c

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "callendar.h"


const size_t LEN = 10;


/**
 * get_wday
 */
bool get_wday(char *buf, unsigned int wday )
{   

const char WDAYS[][LEN] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  if(wday <0 || wday>6 ){
    return false;
}

    strcpy(buf, WDAYS[wday]);
    return true;

}


/**
 * main
 */
int main()
{
    char buf[LEN];

   unsigned int y = 0, m = 0, d = 0;

    printf("Year:");
    scanf("%d", &y);    
    printf("Month:");
    scanf("%d", &m);
   printf("Day:");
    scanf("%d", &d);


unsigned int wday = day_of_week(y, m, d);
if(wday == -1){
printf("invalid value \n");
    return 1;
}

bool ret = get_wday(buf, wday);
if(!ret){
printf("cannot get week day string \n");
    return 1;
}

   printf("Day of week: %s \n", buf);

    return 0;
}
