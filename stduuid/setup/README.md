stduuid: setup
===============


### Install
(1) download souce files  
git clone https://github.com/mariusbancila/stduuid

(2) copy header files to system area 
(eg /usr/local/opt/stduuid)
copy setup_hdr.sh to downloaded directory
% bash setup_lib.sh

(3) copy config file (stduuid.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags stduuid

