openssl
===============

openssl Sample <br/>
get web page from Google with HTTPS  <br/>

openssl : <br/>
a robust, commercial-grade, and full-featured toolkit for the TLS (Transport Layer Security )  and SSL( Secure Sockets Layer) protocols. <br/>
https://www.openssl.org/ <br/>


###  install openssl 
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/openssl/setup <br/>


### https_client.c <br/>
// get web page from Google with HTTPS

build code <br/>
% gcc https_client.c `pkg-config --cflags --libs libssl` <br/>

run code  <br/>
./a.out > result.txt <br/>

display as below <br/>
OpenSSL 1.1.1g  21 Apr 2020 <br/>
ip address : 216.58.197.132 <br/>
Conntect to www.google.com <br/>

### bio <br/>
connect Google using BIO_new_connect <br/>

### Reference <br/>
- https://github.com/openssl/openssl
