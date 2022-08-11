// Number of days between two dates
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


time_t get_time
   (int const y, unsigned int const m, unsigned int const d)
{

struct tm tm1 = { 0 };

	//2001年2月3日 12:34:56を設定
	tm1.tm_year = y - 1900;
	tm1.tm_mon = m - 1;
	tm1.tm_mday = d;

	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 0;

	//tm構造体をtime_t型に変換
	time_t t = mktime(&tm1);
    return t;
}


int number_of_days(
   int const y1, unsigned int const m1, unsigned int const d1,
   int const y2, unsigned int const m2, unsigned int const d2)
{
time_t days1 = get_time(y1, m1, d1);
time_t days2 = get_time(y2, m2, d2);
int days = labs(days1 - days2 )/(24*60*60);

   return days;
}

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

   printf("Days between: %d \n", number_of_days(y1, m1, d1, y2, m2, d2) );

    return 0;
}

