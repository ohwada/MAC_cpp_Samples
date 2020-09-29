time
===============

C++ Sample <br/>
get formated local time <br/>


### system_time_format.hpp
get formated local time <br/>

- getNow()
- formatTime()
- formatGmTimeNow()
- formatJstTimeNow()
- formatGmTime()
- formatJstTime()


build code <br/>
% g++  test_time_format.cpp -std=c++11 <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
2020-08-29 (Sat) 01:52:03 UTC <br/>
2020-08-29 (土) 10:52:03 JST <br/>


### cpuclock.cpp
this sample demonstrates the difference between clock() time and real time <br/>

build code <br/>
% g++  cpuclock.cpp <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
CPU time used: 975.85 ms <br/>
Wall clock time passed: 491.12 ms <br/>


### timespec_get.cpp
display current time with nanoseconds <br/>

build code <br/>
% g++  timespec_get.cpp  -std=c++17 <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
Current time: 09/20/20 13:10:01 JST <br/>
nanos: 525291000 <br/>


### Reference
- http://www.cplusplus.com/reference/ctime/localtime/
- https://en.cppreference.com/w/cpp/chrono/c/clock
- https://en.cppreference.com/w/c/chrono/timespec_get



