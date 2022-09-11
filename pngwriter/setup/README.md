pngriter: setup
===============


### Require  
-  libpng  
- freetype  




### Install  
(1) Download source files
% git clone https://github.com/pngwriter/pngwriter

(1) Create shared libraly (libpngwriter.a) 
build with self-made Makefile
copy Makefile to downloaded directory (pngwriter)  
% mkdir lib  
% make  

TODO:
error occurs in the shared library 
built with the enclosed CMakeLists.txt
> libpng warning: Application built with libpng-1.4.12 but running with 1.6.37  

(2) copy header files and lib files to system area 
(eg /usr/local/opt/pngriter)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(3) copy config file (pngwriter.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs pngwriter
