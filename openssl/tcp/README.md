tcp - openssl
===============

openssl Sample <br/>
TCP Client and server


### sample code
- echo_client.c <br/>
SSL Echo Client for SSL Echo server <br/>
- echo_server.c <br/>
SSL Echo Server <br/>
- version c <br/>
display version <br/>

build code <br/>
% gcc tcp/echo_server.c `pkg-config --cflags --libs openssl` -o server <br/>

run code  <br/>
Usage: ./server <br/>

display as below <br/>
> listen port: 4433  <br/>


### Reference <br/>
- https://github.com/openssl/openssl

