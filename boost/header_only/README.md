header only - boost
===============

boost Sample <br/>

features available with header only <br/>
https://www.boost.org/doc/libs/1_75_0/more/getting_started/unix-variants.html#header-only-libraries <br/>


### sample code <br/>
- to_upper.cpp <br/>
convert lowercase letters to uppercase <br/>
- split.cpp <br/>
split string <br/>
- string_replace_all.cpp <br/>
- format.cpp  <br/>
output with formating like prinf()  <br/>
- version.cpp <br/>
display version <br/>


build code <br/>
% g++ to_upper.cpp  -std=c++11 `pkg-config --cflags --libs boost` <br/>

run code  <br/>
 ./a.out <br/>

display as below <br/>
> original :  hello world!  <br/>
> to_upper :  HELLO WORLD!  <br/>


### Reference <br/>
- https://www.boost.org/

