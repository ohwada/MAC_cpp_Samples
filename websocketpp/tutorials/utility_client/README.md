websocetpp:  tutorials utility_client
===============

The files in this directory are modified versions of  downloaded from below  
https://github.com/zaphoyd/websocketpp/tree/master/tutorials/utility_client


### Require
- standalone asio  
or  
- boost asio  


### samples
- step1.cpp  
A basic program loop that prompts the user for a command and then processes it.   

- step2.cpp  
Add WebSocket++ includes and set up an endpoint type.  

- step3.cpp  
Create endpoint wrapper object that handles initialization and setting up the background thread.  

- step4.cpp  
Opening WebSocket connections  

- step5.cpp  
Closing connections  

- step6.cpp  
Sending and receiving messages

Build and run:
% make step1
% bin/step1
> "Enter Command: ( e.g. help )


