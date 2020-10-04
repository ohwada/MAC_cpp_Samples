/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// GetCurrentTimeNanos
// reference https://abseil.io/docs/cpp/guides/time

#include <iostream>
#include "absl/time/time.h"
#include "absl/time/clock.h"

using namespace std;



/**
 * main
 */
int main(void) 
{

    const char FROMAT[] = "%Y-%m-%d %H:%M:%S %Z";

    int64_t nanos1 =  absl::GetCurrentTimeNanos();

    absl::Time time = absl::FromUnixNanos(nanos1);

    string format = absl::FormatTime( FROMAT, time, absl::LocalTimeZone() );

    cout << " nanos1: " <<   nanos1 << endl;
    cout << "time: " <<  time << endl;
    cout << "format: " <<  format << endl;

    int64_t nanos2 =  absl::GetCurrentTimeNanos();

    int64_t  diff = nanos2 - nanos1;
    absl::Duration duration = absl::Nanoseconds( diff );

    cout << " nanos2: " << nanos2 << endl;
    cout << " diff: " << diff << " nsec" << endl;
    cout << "duration: " << duration << endl;

    return 0;
}


// nanos1: 1600652043011390000
// time: 2020-09-21T10:34:03.01139+09:00
// format: 2020-09-21 10:34:03 JST
// nanos2: 1600652043012709000
// diff: 1319000 nsec
// duration: 1.319ms

