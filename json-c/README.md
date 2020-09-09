json-c
===============

json-c sample <br/>
parse JSON using json-c <br/>

json-c : JSON parser for C <br/>
https://github.com/json-c/json-c/wiki <br/>

### install json-c
% brew install json-c <br/>
https://formulae.brew.sh/formula/json-c <br/>

### test2.cpp
parse JSON from string <br/>
and convert to string <br/>

build code  <br/>
% g++ test2.cpp `pkg-config --cflags --libs json-c` <br/>

run code <br/>
% ./a.out > result.txt <br/>

compare with expected value <br/>
% diff -s result.txt assets/test2_expected.txt <br/>
Files are identical <br/>


### parse.c
psrse JSON from file <br/>


build code  <br/>
% gcc src/parse.c `pkg-config --cflags --libs json-c` -o parse

run code <br/>
Usage: ./parse \< jsonFile \>  <br/>
ex) <br/>
% ./parse assets/sample1.json <br/>

display as below  <br/>
 test_parse_obj_to_string  <br/>
-- 	test_integer: 12345 <br/>
-- 	test_double: 987.654321 <br/>
-- 	test_string: "joys of programming" <br/>

### Reference <br/>
- https://github.com/json-c/json-c
- http://json-c.github.io/json-c/json-c-current-release/doc/html/index.html

