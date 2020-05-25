libiconv
===============

libiconv Sample <br/>
convert text file codeset to UTF8 <br/>

International Codeset Conversion Library <br/>
https://www.gnu.org/software/libiconv/  <br/>

###  TODO
suport utf16, utf32 <br/>

###  install libiconv
% brew install libiconv  <br/>
https://formulae.brew.sh/formula/libiconv  <br/>

## test_convChars.cpp <br/>
convert text codeset to UTF8 <br/>

### build sample code
% g++ test_convChars.cpp TextEncodeConverter.cpp  parse_filename.cpp -o test -I/usr/local/Cellar/libiconv/1.16/include -L/usr/local/Cellar/libiconv/1.16/lib -liconv

### run sample code 
%  ./test <br/>

display as below <br/>
libiconv Version: 1.16 <br/>
sjis: あいうえお <br/>

## read_utf8.cpp <br/>
read UTF8 file <br/>

### build sample code
% g++  read_utf8.cpp TextReader.cpp  -o read <br/>

### run sample code 
Usage: ./read \< textFile \> [debug] 
ex)
% ./read ./samples/sample_utf8.txt <br/>

display as below <br/>
1 : utf8 <br/>
2 : 吾輩は猫である。 <br/>

## conv_file.cpp <br/>
convert text file codeset to UTF8 <br/>

### build sample code
% g++ conv_file.cpp TextReader.cpp TextEncodeConverter.cpp  parse_filename.cpp -o conv -I/usr/local/Cellar/libiconv/1.16/include -L/usr/local/Cellar/libiconv/1.16/lib -liconv <br/>

### run sample code 
Usage: ./conv \< textFile \>  [debug] <br/>
ex)
% ./conv ./samples/sample_sjis.txt <br/>

saved: sample_sjis_utf8.txt <br/>

### Reference <br/>
- https://www.gnu.org/software/libiconv/
- https://www.mk-mode.com/blog/2014/08/24/cpp-convert-sjis-to-utf8/

