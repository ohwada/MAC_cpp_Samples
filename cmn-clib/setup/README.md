cmn-clib: setup
===============


### Install  
(1) download souce files  
git clone https://github.com/kumagaihs/cmn-clib  

(2) Create libcmn-clib.a  
cd downloaded directory (cmn-clib)  

% cd cmn-clib/cmn-clib  
% make  

(3) copy header files and lib files to system area 
(eg /usr/local/opt/cmn-clib)  
copy setup_lib.sh to cmn-clib  
% bash setup_lib.sh  

(4) copy config file (cmn-clib.pc) to system area 
% bash setup_pkgconfig.sh  
% pkg-config --cflags --libs cmn-clib  

