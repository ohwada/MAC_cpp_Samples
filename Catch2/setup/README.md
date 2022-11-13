Catch2: setup
===============


### Install
(1) Download souce files  
git clone https://github.com/catchorg/Catch2

(2) Create libCatch2.a
cd downloaded directory (Catch2)  

% mkdir build  
% cd build  
% cmake ..  
% make  

created src/libCatch2.a and libCatch2Main.a

(3) copy header files and lib files to system area 
(eg /usr/local/opt/Catch2)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs catch2


