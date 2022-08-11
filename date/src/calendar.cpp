/**
 *  calendar.cpp
 * Monthly Calendar
 * 2022-06-01 K.OHWADA
 */

//  g++  calendar.cpp -std=c++11

#include <iostream>
#include <iomanip>
#include "date.h"
#include "iso_week.h"

using namespace std;
using namespace date;


/**
 *  week_day
 */
unsigned int week_day(int const y, unsigned int const m, unsigned int const d)
{

   
   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

   return (unsigned int)tiso.weekday();
}


/**
 *  main
 */
void print_month_calendar(int const y, unsigned int m)
{

   cout << "Mon Tue Wed Thu Fri Sat Sun" << endl;

   auto first_day_weekday = week_day(y, m, 1);
   auto last_day = (unsigned int)year_month_day_last(
      year{ y }, month_day_last{ month{ m } }).day();
   
   unsigned int index = 1;
   for (unsigned int day = 1; day < first_day_weekday; ++day, ++index)
   {
      cout << "    ";
   }

   for (unsigned int day = 1; day <= last_day; ++day)
   {
      cout
         << std::right << std::setfill(' ') << setw(3)
         << day << ' ';
      if (index++ % 7 == 0) 
         std::cout << endl;
   }

   cout << endl;
}


/**
 *  main
 */
int main()
{
   unsigned int y = 0, m = 0;

   cout << "Year:"; cin >> y;
   cout << "Month:"; cin >> m;

   print_month_calendar(y, m);

    return 0;
}
