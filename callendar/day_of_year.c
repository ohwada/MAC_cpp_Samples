/**
 * day_of_year.c
 * Day and week of the year
 * 2022-06-01 K.OHWADA
 */

// gcc day_of_year.c

#include <stdio.h>
#include "time_util.h"


/**
 * main
 */
int main()
{

   unsigned int y = 0, m = 0, d = 0;

    printf("Year:");
    scanf("%d", &y);    
    printf("Month:");
    scanf("%d", &m);
   printf("Day:");
    scanf("%d", &d);

   printf("Day of year: %d \n", day_of_year(y, m, d) );

   printf("Calendar week: %d \n", week_of_year(y, m, d) );

    return 0;
}


// Day of year: 223 
// Calendar week: 32 

