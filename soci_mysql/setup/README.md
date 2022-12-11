soci mysql: setup
===============


### Install
(1) download souce files  
git clone  https://github.com/SOCI/soci

(2) Create libsoci_core.a
cd downloaded directory(soci)  
% mkdir build  
% cd build  
% cmake ..  
% make  

(3) copy header files and lib files to system area   
(eg /usr/local/opt/soci)  
copy setup_lib.sh to downloaded directory  
% bash setup_lib.sh  

(4) copy config file (soci_mysql.pc) to system area   
% bash setup_pkgconfig.sh  
% pkg-config --cflags --libs soci_mysql  


### Note
Version "4_0_3"  is installed, 
but Missing mysql backend
when installed with brew,
The latest version on Github is version "4_1_0"
and include mysql backend

