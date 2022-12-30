boost_asio: ws_client_async
===============

Websocket Client using Boost.Asio

This Client has two mode
(1) In Normal mode
send first Text after opening handshake
send Ping when recieve Text
send new Text  when recieve Pong
send Close when reached the set value
(2) In Echo mode
echo back Text  when recieve Text


### sample code
- ws_client_async.cpp

Build and Run:  
% make client  
% bin/client  
> HTTP/1.1 101 Switching Protocols  

