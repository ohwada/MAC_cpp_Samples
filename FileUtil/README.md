FileUtil
===============

C++ Sample <br/>

## C++ sample code
- read_write_text.cpp <br/>
read and write Text File <br/>
- test_parse_filename.cpp <br/>
parse file fullpath to dir name, file name, file extension <br/> <br/>


build sample code <br/>
% g++  src/read_write_text.cpp -std=c++11 <br/>

run sample code <br/>
Usage:  ./a.out \< Input filename \> \< Output filename \>
ex) <br/>
% ./a.out ./data/sample.txt output.txt <br/>

display as below <br/>
> write to: output.txt <br/>


## C sample code
- test_c_parse_filename.c <br/>
parse fuilepath  <br/>
- file_exists.c <br/>
check file exists <br/>
- copy_file.c <br/>
copy file <br/>
- rename_file.c <br/>
rename file <br/>
read_write_text_file.c <br/>
read and write text file <br/>


build sample code <br/>
% gcc  c_src/test_c_parse_filename.c <br/>

run sample code <br/>
Usage: ./a.out \< filepath \>  <br/>
ex)  <br/>
% ./a.out data/sample.txt  <br/>

display as below  <br/>
> filepath: data/sample.txt 
> filename_with_ext: sample.txt 
> filename_without_ext: sample 
> ext: txt 

