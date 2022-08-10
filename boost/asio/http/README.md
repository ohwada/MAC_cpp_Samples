tcp - boost asio
===============

boost Sample <br/>
http client and server <br/>


### sample code
- http_client.cpp <br/>
HTTP Client<br/>
- http_server.cpp <br/>
HTTP Server <br/>


build code  <br/>
% g++ http_server.cpp -std=c++11 `pkg-config --cflags --libs boost` -o server  <br/>

run code  <br/>
% ./server  [port] <br/>

display as below  <br/>
> listen port: 8080  <br/>

access localhost:8080 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/boost/screenshot/chrome_http_server.png" width="300" />

### Reference <br/>
- https://www.boost.org/

