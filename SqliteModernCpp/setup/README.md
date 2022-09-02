SqliteModernCpp: setup
===============


### setup  
(1) Down load souce files  
% git clone https://github.com/SqliteModernCpp/sqlite_modern_cpp  

(2)copy header files to system area   
(eg /usr/local/opt/sqlite_modern_cpp)  
copy setup_hdr.sh to downloaded directory
(maybe sqlite_modern_cpp)
% bash setup_hdr.sh

(3) copy config file (sqlite_modern_cpp.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs  sqlite_modern_cpp

Note:
if You install it in the following way
% ./configure
% make
 % sudo make install

You get warnings by brew doctor
> Unexpected header files:
 > /usr/local/include/sqlite_modern_cpp.h

