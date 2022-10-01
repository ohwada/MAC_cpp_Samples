httpxx: setup
===============


### Install
(1) download souce files  
% git clone https://github.com/storozhilov/httpxx

(2) Create static shared libraly (libhttpxx.a)  
copy Makefile to downloaded directory (httpxx)  
% make  

Note:
if dynamic library
don't work well

(3) copy header files and lib files to system area 
(eg /usr/local/opt/httpxx)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (httpxx.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs httpxx

