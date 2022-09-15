ZipLib: setup
===============

Require:  
- bzip2 
- lzma 
- zlib 

### Install
(2) create shared liblary(libziplib.a)
% cd ZipLib  
% mkdir build 
% cd build  
% cmake ..  
% make  
> created libziplib.a  

(3)copy header files and lib files to system area 
(eg /usr/local/opt/ZipLib)
% bash setup_lib.sh

(3) copy config file (ziplib.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs ziplib

