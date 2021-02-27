https - openssl
===============

openssl Sample <br/>
HTTPS Client and server


### sample code

- https_server_self_signed.c <br/>
HTTPS Server  using self signed certficate <br/>
- https_server_root_signed.c <br/>
HTTPS Server  using root signed certficate with SAN<br/>
- https_server_add_extra_chain_cert.c <br/>
build certificate chain with add_extra_chain_cert <br/>
- https_client.c <br/>
HTTPS Client without server certification verification <br/>
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

### Document
- https://ken-ohwada.hatenadiary.org/entry/2021/02/22/160855 <br/>
- https://ken-ohwada.hatenadiary.org/entry/2021/02/24/135909 <br/>
- https://ken-ohwada.hatenadiary.org/entry/2021/02/27/113436 <br/>

### Reference 
- https://github.com/openssl/openssl

