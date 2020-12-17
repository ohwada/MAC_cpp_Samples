tcp - boost
===============

boost asio Sample <br/>
tcp client and server <br/>


### sample code
- echo-client.cpp <br/>
TCP Client for Echo server <br/>
- echo_server.cpp <br/>
TCP Echo Server <br/>
- version.cpp <br/>
display version <br/>

build code  <br/>
% g++ echo_server.cpp -std=c++11 `pkg-config --cflags --libs boost` -o server  <br/>

run code  <br/>
% ./server  <br/>

display as below  <br/>
> listen port: 1234  <br/>

### Reference <br/>
- https://www.boost.org/

