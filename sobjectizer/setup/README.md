sobjectizer: setup
===============

### Require  
The 5.7-branch of SObjectizer requires C++17.  
Current version is 5.7.4.2  

### Install
(1) Download souce files  
git clone https://github.com/Stiffstream/sobjectizer

(2) Create /libso_s.xxx.a
cd downloaded directory (sobjectizer)  

% mkdir build  
% cd build  
% cmake ..  
% make  

created so_5/libso_s.5.7.4.2.a and libso.5.7.4.2.dylib

(3) copy header files and lib files to system area 
(eg /usr/local/opt/sobjectizer)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (sobjectizer.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs sobjectizer


