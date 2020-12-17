http : boost_beast
===============

beast samples <br/>
HTTP Client and Server

### sample code
- http_client.cpp <br/>
HTTP Client, synchronous <br/>
- http_server.cpp <br
HTTP Server, synchronous <br/>


### build sample code
g++ http/http_server.cpp -std=c++11 `pkg-config --cflags --libs boost` -o server 

### run sample code
Usage: ./server  [address] [port] [doc_root] <br/>

display as below <br/>
> listen: 8080 <br/>

access localhost:8080 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/boost_beast/screenshot/chrome_http_server.png" width="300" />

### Reference <br/>
- https://www.boost.org/

