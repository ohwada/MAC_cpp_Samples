codecvt
===============

codecvt Sample <br/>
convert UTF-8 to/from UTF-16 <br/>

The codecvt standard facet translates between two different character encodings <br/>
http://www.cplusplus.com/reference/locale/codecvt/ <br/>

### Note
codecvt is deprecated from c ++ 17 <br/>
https://cpprefjp.github.io/reference/codecvt.html <br/>
try utf_converter <br/>

## test_wstring_convert.cpp <br/>
// convert UTF-8 to/from UTF-16 <br/>

### build sample code
% g++ test_wstring_convert.cpp -o test -std=c++11

### run sample code 
%  ./test <br/>

display as below <br/>
test_wstring_convert.cpp
utf16 to utf8: あいうえお


## conv_file.cpp <br/>
convert text file codeset to UTF8 <br/>

### build sample code
% g++ conv_file.cpp TextReader.cpp parse_filename.cpp -o conv -std=c++11 <br/>

### run sample code 
Usage: ./conv \< textFile \> [debug] <br/>
ex)
% ./conv ./samples/sample_utf16be.txt <br/>

saved: sample_utf16be_utf8.txt <br/>

## utf_converter <br/>
substitute for codecvt <br/>

### Reference <br/>
- http://www.cplusplus.com/reference/locale/codecvt/

