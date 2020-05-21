libiconv
===============

libiconv Sample <br/>
convert text file codeset to UTF8 <br/>

International Codeset Conversion Library <br/>
https://www.gnu.org/software/libiconv/  <br/>

###  TODO
sjis, eucjp, utf16be : good  <br/>
utf16, utf32 : not working properly  <br/>

###  install libiconv
% brew install libiconv  <br/>
https://formulae.brew.sh/formula/libiconv  <br/>

## test_convText.cpp <br/>
convert text codeset to UTF8 <br/>

### build sample code
% g++ test_convText.cpp TextEncodeConverter.cpp  parse_filename.cpp -o test -I/usr/local/Cellar/libiconv/1.16/include -L/usr/local/Cellar/libiconv/1.16/lib -liconv

### run sample code 
%  ./test <br/>

display as below <br/>
libiconv Version: 1.16 <br/>
sjis: あいうえお <br/>


## conv_file.cpp <br/>
convert text file codeset to UTF8 <br/>

### build sample code
% g++ conv_file.cpp TextEncodeConverter.cpp  parse_filename.cpp -o conv -I/usr/local/Cellar/libiconv/1.16/include -L/usr/local/Cellar/libiconv/1.16/lib -liconv <br/>

### run sample code 
Usage: ./conv \< textFile \> <br/>
ex)
% ./conv ./samples/sample_sjis.txt <br/>

saved: sample_sjis_utf8.txt <br/>

### Reference <br/>
- https://www.gnu.org/software/libiconv/
- https://www.mk-mode.com/blog/2014/08/24/cpp-convert-sjis-to-utf8/

