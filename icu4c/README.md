icu4c
===============

icu4c sample <br/>

icu4c : <br/>
C/C++ libraries for Unicode and globalization <br/>
http://site.icu-project.org/home <br/>

###  install icu4c
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/icu4c/setup <br/>

## sample code
- read_file.c <br/>
read sjis file convrt to UTF-8
- version.c <br/>
- display version <br/>
 

build sample code<br/>
% gcc read_file.c  `pkg-config --cflags --libs icu-uc` <br/>

run sample code <br/>
Usage:  ./a.out [file] [charset]  <br/>

display as below <br/>
> data/sjis.txt : 221 bytes <br/>
> 吾輩は猫である <br/>


### Reference <br/>
- http://site.icu-project.org/home

