openssl
===============

openssl Sample <br/>
get web page from Google with https  <br/>

openssl : <br/>
a robust, commercial-grade, and full-featured toolkit for the TLS (Transport Layer Security )  and SSL( Secure Sockets Layer) protocols. <br/>
https://www.openssl.org/ <br/>


###  install openssl 
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/openssl/setup <br/>


### sample code
- https_client.c <br/>
HTTPS Client <br/>
- https_server.c <br/>
simple HTTPS Server <br/>


build code <br/>
% gcc src/https_client.c `pkg-config --cflags --libs openssl` <br/>

run code  <br/>
Usage: ./a.out  [host] [port] <br/>

display as below <br/>
> Conntect to example.com <br/>
> HTTP/1.1 200 OK <br/>
> \<title\>Example Domain  \</title\> <br/>

### bio <br/>
sample for BIO method <br/>
- bio_new_connect.c <br/>
connect HTTP server using BIO_new_connect <br/>
- bio_new_ssl_connect.c <br/>
connect HTTPS srver using BIO_new_ssl_connect <br/>


### Reference <br/>
- https://github.com/openssl/openssl

