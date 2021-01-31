src - time
===============

C++ time sample <br/>


### sample code
- test_time_format.cpp <br/>
display RFC822 / ISO8601 datetime <br/>
- test_timestamp.cpp <br/>
display timesatamp file name <br/>
- cpuclock.cpp <br/>
 this sample demonstrates the difference between clock() time and real time <br/>

- timespec_get.cpp <br/>
display current time with nanoseconds  <br/>
reqiure C++17 <br/>


build code <br/>
% g++ test_time_format.cpp -std=c++11 <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
2020-08-29 (Sat) 01:52:03 UTC
2020-08-29 (土) 10:52:03 JST

### Reference
- http://www.cplusplus.com/reference/ctime/localtime/
- https://en.cppreference.com/w/cpp/chrono/c/clock
- https://en.cppreference.com/w/c/chrono/timespec_get



