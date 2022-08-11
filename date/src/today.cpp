/**
 * today.cpp
 * 2022-06-01 K.OHWADA
 */

//  g++ today.cpp -std=c++11

#include <iostream>
#include "date.h"

using namespace std;


/**
 * main
 */
int main()
{

   date::year_month_day today = date::floor<date::days>(std::chrono::system_clock::now());

 //const std::tm* lt = std::localtime(&today);
  //cout << std::put_time(lt, "%c") << endl;

	cout << today << endl;

}

// 2022-08-10


