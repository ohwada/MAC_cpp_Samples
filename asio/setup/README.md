asio: setup
===============



### Install
(1) Download souce files  
git clone https://github.com/chriskohlhoff/asio/

(2) copy header files to system area 
(eg /usr/local/opt/asio)
copy setup_hdr.sh to downloaded directory
% bash setup_hdr.sh

(3) copy config file (asio.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs asio


