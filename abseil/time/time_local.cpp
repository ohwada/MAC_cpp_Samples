/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// display local time

// for macOS
// g++ localtime.cpp -std=c++11  -framework CoreServices `pkg-config --cflags --libs abseil_time`  

// https://abseil.io/docs/cpp/guides/time


#include <iostream>
#include <string>

#include "absl/time/time.h"
#include "absl/time/clock.h"

using namespace std;


/**
 * main
 */
int main(void) 
{

    const char FROMAT[] = "%Y-%m-%d %H:%M:%S %Z";

    absl::Time now = absl::Now();

    string utc_time = absl::FormatTime( FROMAT, now, absl::UTCTimeZone() );

    string local_time = absl::FormatTime( FROMAT, now, absl::LocalTimeZone() );

    cout << "London: " << utc_time << endl;
    cout << "Tokyo: "<< local_time << endl;

    absl::TimeZone nyc;
    if (!absl::LoadTimeZone("America/New_York", &nyc)) {
        cout << "cannot get NYC time zome" << endl;
        return 1;
    }

    string nyc_time = absl::FormatTime( FROMAT, now,  nyc );

    cout << "NewYork: "<< nyc_time << endl;

    return 0;
}


// London: 2020-09-09 10:02:24 UTC
// Tokyo: 2020-09-09 19:02:24 JST
// NewYork: 2020-09-09 06:02:24 EDT


