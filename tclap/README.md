tclap
===============

tclap sample <br/>
test for command line parser <br/>

TCLAP : <br/>
Templatized C++ Command Line Parser Library <br/>

###  install assimp
% brew install tclap <br/>
https://formulae.brew.sh/formula/tclap <br/>

http://tclap.sourceforge.net/ <br/>

## test.c <br/>
test for command line parser <br/>

build code <br/>
% g++  test.cpp -o test `pkg-config --cflags --libs tclap` <br/>

run sample code <br/>
% .test <br/>

display as below <br/>
PARSE ERROR:  <br/>
             Required argument missing: name <br/>
Brief USAGE:  <br/>
   ./test  [-r] -n <string> [--] [--version] [-h]  <br/>
For complete USAGE and HELP type:  <br/>
   ./test --help  <br/>


### Reference <br/>
- http://tclap.sourceforge.net/manual.html

