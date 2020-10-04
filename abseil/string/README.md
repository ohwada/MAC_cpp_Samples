abseil
===============

abseil Sample <br/>

Strings Library <br/>
The absl/strings library provides classes and utility functions for manipulating and comparing strings, converting other types (such as integers) into strings, or evaluating strings for other usages. Additionally, the strings library also contains utility functions for “string-like”classes that store data within contiguous memory. <br/>
https://abseil.io/docs/cpp/guides/strings <br/>


### sample code
- string_view.cpp <br/>
test for string_view container <br/>
- string_split.cpp <br/>
split string <br/>
- string_join.cpp <br/>
join string <br/>
- string_cat.cpp <br/>
catenate string <br/>
- string_append.cpp <br/>
append string <br/>
- string_substitute.cpp <br/>
substitute string <br/>
- string_contains.cpp <br/>
containg substring in string <br/>
- string_numbers.cpp <br/>
convert string to number <br/>
- string_ascii.cpp <br/>
strip AsciiWhitespace in string <br/>
- string_replace.cpp <br/>
replace substring in string <br/>
- string_split.cpp <br/>
strip prefix or sufix in string <br/>


build code <br/>
% g++ string_view.cpp `pkg-config --cflags --libs abseil_strings` <br/>

run code  <br/>
%  ./a.out <br/>

display as below <br/>
> hello <br/>

### Reference <br/>
- https://abseil.io/docs/cpp/guides/
- https://github.com/abseil/abseil-cpp

