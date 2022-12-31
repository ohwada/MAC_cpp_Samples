boost_asio: ws_server_async
===============

WebSocket Echo Server using Boost.Asio  

This Server has two mode  
 (1) In Echo mode  
echo back Text  when recieve Text  

(2) In Test mode  
send first Text after opening handshake  
send Ping when recieve Text  
send new Text  when recieve Pong  
send Close when reached the set value  

handshake response  
(1) If the request have "Sec-WebSocket-Key" header,   
send back the handshake response.  
as WebSocket opening handshake  
(2) If the request doesn't have "Sec-WebSocket-Key" header,   
send back index.html,   
considered as access from a Web Browser  


### sample code  
- async_tcp_echo_server.cpp  


Build and Run:  
% make server  
% bin/server  
> listen:9090  

