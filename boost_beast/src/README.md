src : boost_beast
===============

beast samples <br/>


### sample code
- http_client.cpp <br/>
HTTP Client, synchronous <br/>
- https_client.cpp <br/>
HTTP SSL Client, synchronous <br/>
- http_server.cpp <br
HTTP Server, synchronous <br/>
- https_server.cpp <br/
HTTP SSL Server, synchronous <br/>


### build sample code
g++ src/http_client.cpp -std=c++11 `pkg-config --cflags --libs boost` 

### run sample code
Usage: ./a.out [host] [port] [target] [HTTP version: 1.0 or 1.1(default)] <br/>

display as below <br/>
> connect: www.example.com : 80 <br/>
> \<title\> Example Domain \</title\> <br/>


### Reference <br/>
- https://www.boost.org/

