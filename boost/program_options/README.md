program_options - boost
===============

boost Sample <br/>

Boost.Program_options <br/>
commandline parser <br/>
https://www.boost.org/doc/libs/1_75_0/doc/html/program_options.html <br/>



### sample code <br/>
- first.cpp <br/>
parse command options <br/>


build code <br/>
% g++ first.cpp -std=c++11  `pkg-config --cflags --libs boost_program_options` <br/>

run code  <br/>
 ./a.out <br/>

display as below <br/>
> Compression level was not set.  <br/>


% ./a.out --help  <br/>
> Allowed options:  <br/>
>  --help                produce help message  <br/>
>  --compression arg     set compression level  <br/>



### Reference <br/>
- https://www.boost.org/

