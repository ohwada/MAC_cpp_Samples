boost_asio: http server
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/boost_asio/screenshots/http_file_server.png" width="300" /> 

HTTP Server  
reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/http/server


### sample code  
- http_hello_server.cpp  
return fixed response "Hello World"  

- http_index_server.cpp  
return fixed response index.html  

- http_file_server.cpp  
return requested file content  


Build and Run:
% make file

% bin/file
> listen port: 8080



