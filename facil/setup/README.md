facil: setup
===============


### Install
(1) download souce files  
git clone  https://github.com/boazsegev/facil.io  

(2) Create   
cd downloaded directory (facil.io)  
% mkdir build  
% cd build  
% cmake ..  
% make  

(3) copy header files and lib files to system area 
(eg /usr/local/opt/facil)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (facil.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs facil

