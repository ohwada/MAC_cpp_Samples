serialization - boost
===============

boost Sample <br/>

serialization <br/>
the reversible deconstruction of an arbitrary set of C++ data structures to a sequence of bytes <br/>
https://www.boost.org/doc/libs/1_75_0/libs/serialization/doc/index.html <br/>


### sample code <br/>
- serialization.cpp <br/>
save and load class to/ from archive file <br/>


build code <br/>
% g++ serialization.cpp  `pkg-config --cflags --libs boost_serialization` <br/>

run code  <br/>
 ./a.out <br/>

display as below <br/>
> name: taro <br/>
> age: 20 <br/>


### Reference <br/>
- https://www.boost.org/

