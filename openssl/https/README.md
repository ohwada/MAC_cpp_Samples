https - openssl
===============

openssl Sample <br/>
HTTPS Client and server


### sample code
- https_client.c <br/>
HTTPS Client without server certification verification<br/>
- https_server.c <br/>
HTTPS Server <br/>
- https_client_verify.c <br/>
HTTPS Client with server certification verification  <br/>
- get certs <br/>
get certificate chain from server <br/>


build code <br/>
% gcc https/https_server.c `pkg-config --cflags --libs openssl` -o server <br/>

run code  <br/>
Usage: ./server <br/>

display as below <br/>
> listen port: 8081  <br/>

access localhost:8081 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/openssl/screenshot/firefox_https_server.png" width="300" />


### Reference <br/>
- https://github.com/openssl/openssl

