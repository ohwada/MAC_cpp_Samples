dlib_gui: setup
===============


build from source  
to enable GUI SUPPORT  


### Install  
(1) Download source files  
% git clone  https://github.com/davisking/dlib/  

(2) Create shared libraly (libdlib.a)   
% cd to downloaded directory( dlib )  
% mkdir build  
 % cd build  
% cmake ..  
% make

(2) copy header files and lib files to system area 
(eg /usr/local/opt/dlib_gui)  
copy setup_lib.sh to downloaded directory( dlib )  
% bash setup_lib.sh  

(3) copy config file (dlib_gui.pc) to system area 
% bash setup_pkgconfig.sh  
% pkg-config --cflags --libs dlib_gui  

