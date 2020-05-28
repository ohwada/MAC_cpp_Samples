boost
===============

boost Sample <br/>

split string <br/>

boost : <br/>
free portable C++ source libraries. <br/>
https://www.boost.org/<br/>

###  install boost
% brew install boost <br/>
https://formulae.brew.sh/formula/boost<br/>

## test_boost_exsample.cpp <br/>
example : to_upper, trim, to_lower_copy <br/>

### build sample code
% c++ test_boost_exsample.cpp -o test  -I/usr/local/Cellar/boost/1.72.0_2/include/ -L/usr/local/Cellar/boost/1.72.0_2/lib -lboost_system <br/>

### run sample code 
 ./test <br/>

display as below <br/>
original :  hello world!  <br/>
to_upper :  HELLO WORLD!  <br/>

## test_split.cpp <br/>
split string <br/>

### build sample code
% c++ test_split.cpp -o split  -I/usr/local/Cellar/boost/1.72.0_2/include/ -L/usr/local/Cellar/boost/1.72.0_2/lib -lboost_system <br/>

### run sample code 
./split <br/>

display as below <br/>
split with ',' 
abc,def,ghi,jkl
abc
def
...


### Reference <br/>
- https://www.boost.org/

