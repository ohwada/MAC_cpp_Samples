/**
 * monthly_calendar.c
 * 2022-06-01 K.OHWADA
 */

// gcc monthly_calendar.c

#include <stdio.h>
#include "calendar.h"


/**
 * print_month_calendar
 */
void print_month_calendar(int const y, unsigned int m)
{

   printf(" Sun Mon Tue Wed Thu Fri Sat \n");

    unsigned int first_day_weekday = day_of_week(y, m, 1) + 1;

    unsigned int  last_day = last_day_of_month(y, m); 


   unsigned int index = 1;
   for (unsigned int day = 1; day < first_day_weekday; ++day, ++index)
   {
    // four spaces
      printf("    ");
   }

   for (unsigned int day = 1; day <= last_day; ++day)
   {
        printf("%4d", day);
        if (index++ % 7 == 0) {
            // Sat
            printf("\n");
        }
   } // for
    printf("\n");
}


/**
 * main
 */
int main()
{
   unsigned int y = 0, m = 0;

    printf("Year:");
    scanf("%d", &y);    
    printf("Month:");
    scanf("%d", &m);

   print_month_calendar(y, m);

    return 0;
}


// Sun Mon Tue Wed Thu Fri Sat 
//       1   2   3   4   5   6
//   7   8   9  10  11  12  13
//  14  15  16  17  18  19  20
//  21  22  23  24  25  26  27
//  28  29  30  31


