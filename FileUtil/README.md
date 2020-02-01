FileUtil
===============

C++ Sample <br/>

## read_write_text.cpp
read and write Text File <br/>

### build and excute sample code 
% g++  read_write_text.cpp -o read_write_text -std=c++11 <br/>
% ./read_write_text ./data/sample.txt output.txt <br/>

### result 
read text file  <br/>  
ex ) sample.txt <br/>
and show text  <br/>

and write to output file  <br/>
 ex ) output.txt  <br/>

## parse_filename.cpp
parse file fullpath to dir name, file name, file extension <br/>

### build sample code
% g++ test_parse_filename.cpp parse_filename.cpp -o test_parse_filename -std=c++11 <br/>

### excute sample code 
% ./test_parse_filename  /etc/sample.txt <br/>

### result 
parse Filename and display as below <br/>
/etc/ , sample , txt <br/>

