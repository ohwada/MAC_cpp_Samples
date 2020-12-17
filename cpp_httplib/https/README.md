https - cpp_httplib
===============

cpp_httplib sample <br/>
HTTPS client and server <br/>



## sample code
- https_client.cpp <br/>
HTTPS client <br/> 
- https_server.cpp <br/>
HTTPS server <br/>


build sample code<br/>
% g++ https/https_server.cpp -std=c++11  `pkg-config --cflags --libs openssl` -o server  <br/>

run sample code <br/>
usage: ./server [port] <br/>

display as below <br/>
> The server started at port 8081... <br/>

access localhost:8081 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/cpp_httplib/screenshot/firefox_https_server.png" width="300" />


### Reference <br/>
- https://github.com/yhirose/cpp-httplib 

