/**
 * days.c 
 * Number of days between two dates
 * 2022-06-01 K.OHWADA
 */

// gcc days.c 

#include <stdio.h>
#include <stdlib.h>
#include "time_util.h"


/**
 * number_of_days
 */
int number_of_days(
   int const y1, unsigned int const m1, unsigned int const d1,
   int const y2, unsigned int const m2, unsigned int const d2)
{
time_t days1 = get_unixtime(y1, m1, d1, 0, 0, 0);
time_t days2 = get_unixtime(y2, m2, d2, 0, 0, 0);
int days = labs(days1 - days2 )/(24*60*60);

   return days;
}


/**
 * main
 */
int main()
{
// Olympic Tokyo 2020 opening day
    unsigned int  y1 = 2021;
    unsigned int  m1 = 7;
    unsigned int  d1 = 23;

   unsigned int y2 = 0, m2 = 0, d2 = 0;

   printf("Year:");
    scanf("%d", &y2);
   printf("Month:");
    scanf("%d", &m2);
   printf("Date:");
    scanf("%d", &d2);

   printf("%d days from Tokyo 2022 \n", number_of_days(y1, m1, d1, y2, m2, d2) );

    return 0;
}

// 383 days from Tokyo 2022 

