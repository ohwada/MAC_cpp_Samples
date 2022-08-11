/**
 * day_of_year.cpp
 * 2022-06-01 K.OHWADA
 */

//  g++ day_of_year.cpp -std=c++11

#include <iostream>
#include "date.h"
#include "iso_week.h"

using namespace std;
using namespace date;


/**
 *  calendar_week
 */
unsigned int calendar_week(int const y, unsigned int const m, unsigned int const d)
{

   
   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

   return (unsigned int)tiso.weeknum();
}


/**
 *  day_of_year
 */
int day_of_year(int const y, unsigned int const m, unsigned int const d)
{

   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   return (sys_days{ year{ y } / month{ m } / day{ d } } -
      sys_days{ year{ y } / jan / 0 }).count();
}


/**
 * main
 */
int main()
{
   int y = 0;
   unsigned int m = 0, d = 0;
   cout << "Year:"; cin >> y;
   cout << "Month:"; cin >> m;
   cout << "Day:"; cin >> d;

   cout << "Calendar week: " << calendar_week(y, m, d) << endl;
   cout << "Day of year: " << day_of_year(y, m, d) << endl;

    return 0;
}

