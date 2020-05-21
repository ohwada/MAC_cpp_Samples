utf_converter. - codecvt
===============

UTF codeset Sample <br/>
convert codeset between UTF-8  UTF-16 UTF-32 <br/>


## test_utf_converter.cpp <br/>
convert text codeset to UTF-8 <br/>

### build sample code
% g++ test_utf_converter.cpp  utf_converter.cpp -o test -std=c++11

### run sample code 
%  ./test <br/>

display as below <br/>
test_utf_converter.cpp
utf16 to utf8: あいうえお
utf32 to utf8: あいうえお


## conv_file.cpp <br/>
convert text file codeset to UTF8 <br/>

### build sample code
% g++ conv_file.cpp utf_converter.cpp  ../parse_filename.cpp -o conv -std=c++11 <br/>

### run sample code 
Usage: ./conv \< textFile \> <br/>
ex)
% ./conv ../samples/sample_utf16be.txt <br/>

saved: sample_utf16be_utf8.txt <br/>

### Reference <br/>
- http://www.cplusplus.com/reference/locale/codecvt/

