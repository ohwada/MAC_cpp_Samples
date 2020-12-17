https : boost_beast
===============

beast samples <br/>
HTTPS Client and Server

### sample code
- https_client.cpp <br/>
HTTP SSL Client, synchronous <br/>
- https_server.cpp <br/
HTTP SSL Server, synchronous <br/>


### build sample code
 % g++ https/https_server.cpp -std=c++11 `pkg-config --cflags --libs boost`  `pkg-config --cflags --libs openssl` -o server

### run sample code
Usage: ./server [address] [port] [doc_root]  <br/>

display as below <br/>
> listen: 8081 <br/>

access localhost:8081 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/boost_beast/screenshot/firefox_https_server.png" width="300" />


### Reference <br/>
- https://www.boost.org/

