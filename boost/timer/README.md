timer - boost
===============

boost Sample <br/>

The Boost Timer library: <br/>
 CPU timers <br/>
https://www.boost.org/doc/libs/1_75_0/libs/timer/doc/index.html <br/>


### sample code <br/>
- auto_cpu_timer.cpp <br/>
When the auto_cpu_timer object is created, it starts timing. <br/>
When it is destroyed at the end of the scope,  its destructor stops the timer and displays timing information on the default output stream, std::cout. <br/>


build code <br/>
% g++ auto_cpu_timer.cpp  -std=c++11 `pkg-config --cflags --libs boost_timer` <br/>

run code  <br/>
 ./a.out <br/>

display as below <br/>
> 0.642409s wall, 0.640000s user + 0.000000s system = 0.640000s CPU (99.6%)  <br/>


### Reference <br/>
- https://www.boost.org/

