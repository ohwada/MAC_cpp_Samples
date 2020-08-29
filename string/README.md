string
===============

C++ Sample <br/>

### string_upper.hpp
string to uppercase / lowercase <br/>

- str2upper();
- str2lower();

build code <br/>
% g++  test_str2upper.cpp  -std=c++11 <br/>

run code <br/>
Usage: ./a.out [mode] <br/>
ex) <br/>
./a.out <br/>

display as below <br/>
please enter the lowercase alphabets <br/>
\> <br/>


### string_replace.hpp
// replace sub string in string <br/>

- replaceString();

build code <br/>
% g++  test_replaceString.cpp  -std=c++11 <br/>

run code <br/>
./a.out <br/>

display as below <br/>
original: <br/>
hello world goodby world <br/>
world -> japan <br/>
replaced: <br/>
hello japan goodby world <br/>


### string_substr.hpp
get the substring sandwiched by the specified words from the string <br/>

- subString();

build code <br/>
% g++  test_subString.cpp  -std=c++11 <br/>

run code <br/>
./a.out <br/>

display as below <br/>
sample1: <br/>
abc#b%123456789$e&xyz  <br/>
begin:#b%  <br/>
end:$e&  <br/>
substr: '123456789'  <br/>
head: 'abc'  <br/>
tail: 'xyz'  <br/>


### Reference
- https://en.cppreference.com/w/cpp/string/basic_string

