libzippp: setup
===============


### Install
(1) download souce files  
% git clone https://github.com/ctabin/libzippp

(2) Create libzippp_static.a  
cd downloaded directory (libzippp)  
% mkdir build  
% cd build  
% cmake ..  
% make  


(3) copy header files and lib files to system area 
(eg /usr/local/opt/lobzippp)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (libzippp.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs libzippp

