sockpp: setup
===============


### Install
(1) download souce files  
% git clone https://github.com/fpagliughi/sockpp

(2) Create libsockpp.a  
cd downloaded directory (sockpp)  
% mkdir build  
% cd build  
% cmake ..   -DSOCKPP_BUILD_STATIC=ON
% make  

Note:
if dynamic library
don't work well

(3) copy header files and lib files to system area 
(eg /usr/local/opt/sockpp)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (sockpp.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs sockpp

