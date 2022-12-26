cwebsocket: setup
===============

### Dependencies
- openssl  
- libev  

### Install
(1) Get soucd files
- original:  
https://github.com/jeremyhahn/cwebsocket 

- modified:
https://github.com/ohwada/MAC_cpp_Samples/tree/master/cwebsocket/cwebsocket  

(2) Build libwsserver.a  libwsclient.a
% ./autogen.sh
% ./configure
% make  

(3) copy header files and lib files to system area 
(eg /usr/local/opt/cwebsocket)  
% bash setup_lib.sh  

(4) copy config file (cwebsocket.pc) to system area 
% bash setup_pkgconfig.sh  
% pkg-config --cflags --libs cwebsocket  


