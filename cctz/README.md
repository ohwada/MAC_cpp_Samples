cctz
===============

cctz sample <br/>
display local time <br/>

cctz : <br/>
C++ library for translating between absolute and civil times <br/>
https://github.com/google/cctz <br/>


###  install cctz
see below <br/>
https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/cctz/setup <br/>


### localtime.cpp
display local time <br/>

build code <br/>
% g++ locatime.cpp `pkg-config --cflags --libs cctz` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
UTC:	 2020-09-14 07:34:35 UTC  <br/>
NYC:	 2020-09-14 03:34:35 EDT <br/>
LA:	     2020-09-14 00:34:35 PDT <br/>
Tokyo:	 2020-09-14 16:34:35 JST <br/>


### Reference <br/>
- https://github.com/google/cctz <br/>

