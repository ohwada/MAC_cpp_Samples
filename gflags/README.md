gflags
===============

gflags sample <br/>
 <br/>

gflags : <br/>
Google Commandline Flag <br/>
users specify on the command line <br/>
https://gflags.github.io/gflags <br/>

### install gflags
% brew install gflags <br/>
https://formulae.brew.sh/formula/gflags <br/>

### append_text.cpp
parse commandline flags <br/>
append text to text file <br/>

build code  <br/>
% g++ append_text.cpp `pkg-config --cflags --libs gflags`  <br/>

run code <br/
% ./a.out <br/>

display as below  <br/>
> Usage: ./a.out --filename \<textFile\> [ --append_text \<yourText\> ] [ -- read ] 
> Help: ./a.out --help

append_text <br/>
> ./a.out --filename hoge.txt --append_text "aaa"
> ./a.out --filename hoge.txt --append_text "bbb"
> ./a.out --filename hoge.txt --read
> aaa
> bbb

### Reference <br/>
- https://github.com/gflags/gflags

