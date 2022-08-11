/**
 * meeting_time.cpp
 * Meeting time for multiple time zones
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <iomanip>
#include "date.h"
#include "tz.h"


/**
 * struct user
 */
struct user
{
   std::string             Name;
   date::time_zone const * Zone;

   user(std::string_view name, std::string_view zone)
      : Name{name.data()}, Zone(date::locate_zone(zone.data()))
   {      
   }
};


using namespace std;
namespace ch = std::chrono;


/**
 * print_meeting_times
 */
template <class Duration, class TimeZonePtr>
void print_meeting_times(
   date::zoned_time<Duration, TimeZonePtr> const & time,
   std::vector<user> const & users)
{
   cout 
      << left << setw(15) << setfill(' ')
      << "Local time: " 
      << time << std::endl;

   for (auto const & user : users)
   {
      cout
         << left << setw(15) << setfill(' ')
         << user.Name
         << date::zoned_time<Duration, TimeZonePtr>(user.Zone, time) 
         << endl;
   }
}


/**
 * main
 */
int main()
{
   std::vector<user> users{
      user{ "Ildiko", "Europe/Budapest" },
      user{ "Jens", "Europe/Berlin" },
      user{ "Jane", "America/New_York" }
   };

   unsigned int h, m;
   cout << "Hour:"; cin >> h;
   cout << "Minutes:"; cin >> m;

   date::year_month_day today = date::floor<date::days>(ch::system_clock::now());

   auto localtime = date::zoned_time<std::chrono::minutes>(
      date::current_zone(), 
      static_cast<date::local_days>(today) + ch::hours{ h } +ch::minutes{ m });

   print_meeting_times(localtime, users);

    return 0;
}


// Local time:    2022-08-10 01:30:00 JST
// Ildiko         2022-08-09 18:30:00 CEST
// Jens           2022-08-09 18:30:00 CEST
// Jane           2022-08-09 12:30:00 EDT

