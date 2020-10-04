flags - abseil
===============

abseil Sample <br/>

The Abseil Flags Library <br/> 
The Abseil flags library allows programmatic access to flag values passed on the command-line to binaries. <br/> 
https://abseil.io/docs/cpp/guides/flags <br/>

### sample codes 
- parse_flags.cpp <br/>
parse comand line flags <br/>
- validate_flag_value.cpp <br/>
//validating Flag Values <br/>


build code <br/>
% g++ parse_flags.cpp   -std=c++11  -framework CoreServices  `pkg-config --cflags --libs abseil_flags`  <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> big menu: true 
> output dir: foo/bar/baz/ 
> timeout: 30s 
> languages: english, french, german,  


% ./a.out -big_menu -output_dir abc -timeout 10s  -languages jpanese,chinese <br/>
> big menu: true
> output dir: abc
>  timeout: 10s
> languages: jpanese, chinese, 

