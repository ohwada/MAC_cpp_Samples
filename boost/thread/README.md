thread - boost
===============

boost Sample <br/>


Boost.Thread <br/>
 enables the use of multiple threads of execution with shared data in portable C++ code <br/>
https://www.boost.org/doc/libs/1_75_0/doc/html/thread.html <br/>


### sample code <br/>
- bank_account.cpp <br/>
the bankAgent will deposit $500 in JoesAccount. <br/>
Joe will similarly withdraw $100 from his account. <br/>


build code <br/>
% g++ bank_account.cpp  -std=c++11 `pkg-config --cflags --libs boost_thread` <br/>

run code  <br/>
 ./a.out <br/>

display as below <br/>
 > bankAgent: 4900 <br/>
 > Joe: 4800 <br/>


### Reference <br/>
- https://www.boost.org/

