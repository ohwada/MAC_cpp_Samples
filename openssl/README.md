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

## sample code

### tcp
TCP Client and server
- echo_client.c <br/>
SSL Echo Client for SSL Echo server <br/>
- echo_server.c <br/>
SSL Echo Server <br/>

### https
HTTPS Client and server
- https_client.c <br/>
HTTPS Client without server certification verification<br/>
- https_server.c <br/>
HTTPS Server <br/>

access localhost:8081 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/openssl/screenshot/firefox_https_server.png" width="300" />

### bio 
sample for BIO method <br/>
- bio_new_connect.c <br/>
connect HTTP server using BIO_new_connect <br/>
- bio_new_ssl_connect.c <br/>
connect HTTPS srver using BIO_new_ssl_connect <

### smime
openssl S/MIME sample <br/>
- test_encrypt.c <br/>
S/MIME encrypt decrypt example <br/>
- test_sign.c <br/>
S/MIME sign verify example <br/>

### verify_cert 
verify X509 certificate <br/>
- verift localhost.c <br/>
verify localhost cert <br/>
- verify_example_org.c <br/>
verify www.example.org cert <br/>


### Reference <br/>
- https://github.com/openssl/openssl

