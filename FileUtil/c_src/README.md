c_src - FileUtil
===============

File Utility <br/>
C version <br/>

## sample code
- test_c_parse_filename.c <br/>
parse fuilepath  <br/>
- test_file_exists.c <br/>
check file exists <br/>
- test_copy_file.c <br/>
copy file <br/>
- test_rename_file.c <br/>
rename file <br/>
- test_read_write_text_file.c <br/>
read and write text file <br/>
- test_read_write_binary_file.c <br/>
read and write binary file  <br/>
- test_file_list.c <br/>
get filenames in directory <br/>

build sample code <br/>
% gcc test_c_parse_filename.c -o parse <br/>

run sample code <br/>
Usage: ./a.out \< filepath \>  <br/>
ex)  <br/>
% ./parse /data/sample.txt  <br/>

display as below  <br/>
> filepath: data/sample.txt  <br/>
> filename_with_ext: sample.txt  <br/>
> filename_without_ext: sample  <br/>
> ext: txt 

