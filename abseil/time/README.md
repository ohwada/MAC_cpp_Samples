abseil
===============

abseil Sample <br/>

Time Library 
This Abseil time library contains abstractions for holding time values, both in terms of absolute time and civil time. <br/>
https://abseil.io/docs/cpp/guides/time <br/>


### sample code
- time_local.cpp <br/>
// display local time <br/>
- time_current_nanos.cpp <br/>
GetCurrentTimeNanos <br/>


build code <br/>
% g++ time_local.cpp `pkg-config --cflags --libs abseil_time`  <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> London: 2020-09-09 10:02:24 UTC
> Tokyo: 2020-09-09 19:02:24 JST
> NewYork: 2020-09-09 06:02:24 EDT

### Reference <br/>
- https://abseil.io/docs/cpp/guides/
- https://github.com/abseil/abseil-cpp

