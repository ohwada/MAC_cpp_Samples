cwebsocket
===============

This is Clone  
https://github.com/jeremyhahn/cwebsocket  

### About
 High performance websocket client/server  

see detail  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/cwebsocket/README_orig.md  

### Changes:  
cwebsocket/server.c  
(1) allow "Connection: keep-alive, Upgrade"  
(2) ignore "Resource temporarily unavailable"  
in cwebsocket_server_read_data  
(3) added wait to recieve request  
in cwebsocket_server_read_handshake  
(4) allways echo back text frame  
(5) allow close frame without code without reason  
(6) return close frame  
(7) return pong frame  

### Build  
% ./autogen.sh  
% ./configure  
% make  
created libwsserver.a libwsclient.a  
% bash setup_lib.sh  

