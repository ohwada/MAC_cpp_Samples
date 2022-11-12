Clara: setup
===============


### Install
(1) Download souce files  
git clone https://github.com/catchorg/Clara

(2) copy header files to system area 
(eg /usr/local/opt/clara)
copy setup_hdr.sh to downloaded directory
% bash setup_hdr.sh

(3) copy config file (clara.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags clara


