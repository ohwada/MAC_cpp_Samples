numeric - abseil
===============

abseil Sample <br/>

The Numeric Library <br/>
The //absl/numeric library provides only one header file int128.h at this time: <br/>
128-bit Integers<br/>
The int128.h header file defines signed and unsigned 128-bit integer types. <br/>
https://abseil.io/docs/cpp/guides/numeric <br/>

### sample code
- make_uint128.cpp <br/>
sample for MakeUint128 <br/>
- make_int128.cpp <br/>
sample for MakeInt128 <br/>

build code <br/>
% g++ make_uint128.cpp `pkg-config --cflags --libs abseil_numeric`  <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> big : 10000000000000000 <br/>
> high :0 <br/>
> low : ffffffffffffffff <br/>


### Reference <br/>
- https://abseil.io/docs/cpp/guides/
- https://github.com/abseil/abseil-cpp

