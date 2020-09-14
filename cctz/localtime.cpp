/**
 * cctz sample
 * 2020-03-01 K.OHWADA
 */

// display local time

// original : https://github.com/google/cctz/blob/master/examples/example3.cc

// Copyright 2016 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   https://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include <chrono>
#include <iostream>
#include <string>
#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

using namespace std;


/**
 * main
 */
int main(void) {

     cctz::time_zone utc;
    load_time_zone("UTC", &utc);

    cctz::time_zone tky;
    load_time_zone("Asia/Tokyo", &tky);

    cctz::time_zone nyc;
    load_time_zone("America/New_York", &nyc);

    cctz::time_zone lax;
    load_time_zone("America/Los_Angeles", &lax);


    const auto now = std::chrono::system_clock::now();
    const cctz::civil_second cs = cctz::convert(now, utc);

    cout << cctz::format("UTC:\t %Y-%m-%d %H:%M:%S %Z ", now, utc) << endl;

    cout << cctz::format("NYC:\t %Y-%m-%d %H:%M:%S %Z", now, nyc) << endl;

    cout << cctz::format("LA:\t %Y-%m-%d %H:%M:%S %Z", now, lax) << endl;

    cout << cctz::format("Tokyo:\t %Y-%m-%d %H:%M:%S %Z", now, tky) << endl;

    return 0;
}


// UTC:	 2020-09-14 07:34:35 UTC 
// NYC:	 2020-09-14 03:34:35 EDT
// LA:	 2020-09-14 00:34:35 PDT
// Tokyo:	 2020-09-14 16:34:35 JST

