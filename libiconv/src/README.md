src - libiconv
===============

libiconv Sample <br/>
convert text codeset <br/>

###  TODO
suport utf16, utf32 <br/>


### sample code
- test_convChars.cpp <br/>
convert text codeset to UTF8 <br/>
- read_utf8.cpp <br/>
read UTF8 file <br/>
- conv_file.cpp <br/>
convert text file codeset to UTF8 <br/>
- read_utf8.cpp <br/>
read UTF8 file <br/>
- test_iso2022jp.c <br/>
convert codeset ISO2022_JP to UTF-8 <br/>
- write_iso2022jp.cpp <br/>
convert codeset UTF-8 to ISO2022_JP  <br/>
- read_iso2022jp.cpp <br/>
convert codeset ISO2022_JP to UTF-8 <br/>


build sample code <br/>
% g++ test_convChars.cpp TextEncodeConverter.cpp  `pkg-config --cflags --libs iconv`  -o test 


run sample code <br/>
%  ./test <br/>

display as below <br/>
libiconv Version: 1.16 <br/>
sjis: あいうえお <br/>



### Reference <br/>
- https://www.gnu.org/software/libiconv/
- https://www.mk-mode.com/blog/2014/08/24/cpp-convert-sjis-to-utf8/

