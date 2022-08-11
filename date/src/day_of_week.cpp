/**
 * day_of_week.cpp
 * 2022-06-01 K.OHWADA
 */

//  g++ day_of_week.cpp -std=c++11

#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "iso_week.h"

   using namespace std;
   using namespace date;


/**
 * get_wday
 */
string get_wday(unsigned int wday )
{   
const vector<string> WDAYS{ "", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

    string ret(""); 
    if(wday >=1 && wday<=7 ){
        ret = WDAYS[wday];
    }

   return ret;
}


/**
 * week_day
 */
unsigned int week_day(
int const y, unsigned int const m, unsigned int const d)
{   
   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

    return (unsigned int)tiso.weekday();
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

    auto wday = week_day(y, m, d);

   cout << "Day of week: " << get_wday(wday) << endl;

    return 0;
}
