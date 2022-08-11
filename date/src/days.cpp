/**
 * days.cpp
 * Number of days between two dates
 * 2022-06-01 K.OHWADA
 */

//  g++ days.cpp -std=c++11


#include <iostream>
#include <cmath>
#include "date.h"

  using namespace date;

sys_days get_days
   (int const y, unsigned int const m, unsigned int const d)
{
    return sys_days{ year{ y } / month{ m } / day{ d } };
}

int number_of_days(
   int const y1, unsigned int const m1, unsigned int const d1,
   int const y2, unsigned int const m2, unsigned int const d2)
{
auto days1 = get_days(y1, m1, d1);
auto days2 = get_days(y2, m2, d2);
auto days = (days1 - days2 ).count();

   return abs(days);
}

int main()
{
// Olympic Tokyo 2020 opening day
    unsigned int  y1 = 2021;
    unsigned int  m1 = 7;
    unsigned int  d1 = 23;

   unsigned int y2 = 0, m2 = 0, d2 = 0;
   std::cout << "Year:"; std::cin >> y2;
   std::cout << "Month:"; std::cin >> m2;
   std::cout << "Date:"; std::cin >> d2;

   std::cout << "Days between: " << number_of_days(y1, m1, d1, y2, m2, d2) << std::endl;

    return 0;
}

