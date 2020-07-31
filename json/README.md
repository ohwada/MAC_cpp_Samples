json
===============

C json sample <br/>
parse json using json-c <br/>

json-c : JSON parser for C
https://github.com/json-c/json-c/wiki

### install json-c
% brew install json-c
https://formulae.brew.sh/formula/json-c

### test2.c
simple test <br/>
parse json from string <br/>
and convert to string <br/>

build code  <br/>
% gcc src/test2.c -o test `pkg-config --cflags --libs json-c` 

run code <br/>
% ./test > result.txt <br/>

compare with expected value <br/>
% diff -s result.txt assets/test2_expected.txt <br/>
Files are identical <br/>


### parse.c
psrse json from file <br/>


build code  <br/>
% gcc src/parse.c -o parse `pkg-config --cflags --libs json-c` 

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

