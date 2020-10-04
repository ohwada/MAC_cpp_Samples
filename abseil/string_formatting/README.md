abseil
===============

abseil Sample <br/>

String Formatting <br/>
absl::StrFormat() <br/>
The str_format library is a typesafe replacement for the family of printf() string formatting routines within the <cstdio> standard library header.  <br/>
The str_format library provides most of the functionality of printf() type string formatting and a number of additional benefits: <br/>
https://abseil.io/docs/cpp/guides/format <br/>

### sample code
- format_string.cpp <br/>
format string like sprintf <br/>

build code <br/>
% g++ string_format.cpp `pkg-config --cflags --libs abseil_str_format` <br/>

run code  <br/>
%  ./a.out <br/>

display as below <br/>
> Welcome to The Village, Number 6! <br/>

### Reference <br/>
- https://abseil.io/docs/cpp/guides/
- https://github.com/abseil/abseil-cpp

