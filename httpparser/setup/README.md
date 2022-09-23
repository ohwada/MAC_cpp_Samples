httpparser: setup
===============


### Install
(1) download souce files  
git clone  https://github.com/nekipelov/httpparser

(2) copy header files to system area 
(eg /usr/local/opt/httpparser)
copy setup_hdr.sh to downloaded directory
% bash setup_hdr.sh

(3) copy config file (httpparser.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags httpparser

