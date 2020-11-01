c_src - FileUtil
===============

C File Utility <br/>

## sample code
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
read_write_binary_file.c <br/>
// read and write binary file  <br/>

build sample code <br/>
% gcc  c_src/test_c_parse_filename.c <br/>

run sample code <br/>
Usage: ./a.out \< filepath \>  <br/>
ex)  <br/>
% ./a.out data/sample.txt  <br/>

display as below  <br/>
> filepath: data/sample.txt  <br/>
> filename_with_ext: sample.txt  <br/>
> filename_without_ext: sample  <br/>
> ext: txt 

