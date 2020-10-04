hash - abseil
===============

abseil Sample <br/>

Hash Library <br/>
This library is designed to be used as a replacement for std::hash and various other hash functors. <br/>
https://abseil.io/docs/cpp/guides/hash <br/>

### sample codes 
- hash_circle.cpp <br/>
generate a hash value for the class <br/>

build code <br/>
% g++ hash_circle.cpp `pkg-config --cflags --libs abseil_hash`  <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> [ 3, 4 ] => [ 33, 4 ]  <br/>
> [ 2, 3 ] => [ 22, 3 ]  <br/>
> [ 1, 2 ] => [ 11, 2 ]  <br/>

