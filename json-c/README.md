json-c
===============

json-c sample <br/>
parse JSON using json-c <br/>

json-c : JSON parser for C <br/>
https://github.com/json-c/json-c/wiki <br/>

### install json-c
% brew install json-c <br/>
https://formulae.brew.sh/formula/json-c <br/>


### sample code
- test2.cpp <br/>
parse JSON from string <br/>
- parse_from_file.c <br/>
psrse JSON from file <br/>
- parse_from_string.c <br/>
psrse JSON from string <br/>
- parse_mail.c <br/>
parse mail json file <br/>

build code  <br/>
% gcc src/test2.c `pkg-config --cflags --libs json-c` <br/>

run code <br/>
% ./a.out > result.txt <br/>

compare with expected value <br/>
% diff -s result.txt assets/test2_expected.txt <br/>
Files are identical <br/>

### Reference <br/>
- https://github.com/json-c/json-c
- http://json-c.github.io/json-c/json-c-current-release/doc/html/index.html

