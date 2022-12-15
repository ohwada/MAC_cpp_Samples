websocetpp:  tutorials utility_server
===============

The files in this directory are modified versions of  downloaded from below  
https://github.com/zaphoyd/websocketpp/tree/master/tutorials/utility_server

### Require
- standalone asio  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/asio  
or  
- boost asio  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/boost_asio  

### samples
- step1.cpp  
Add WebSocket++ includes and set up a a server endpoint type.

- step2.cpp  
Set up a message handler to echo all replies back to the original user
 

Build and run:
% make step1
% bin/step1
> listen: 9002


Client
run ws_client.html by web brawser  

