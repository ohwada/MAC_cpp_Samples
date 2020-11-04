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


### https_client.c <br/>
// get web page from HTTP server with HTTPS

build code <br/>
% gcc https_client.c `pkg-config --cflags --libs libssl` <br/>

run code  <br/>
./a.out > result.txt <br/>

display as below <br/>
> Conntect to "example.com <br/>

### bio <br/>
 vconnect HTTP server using BIO_new_connect <br/>

### Reference <br/>
- https://github.com/openssl/openssl

