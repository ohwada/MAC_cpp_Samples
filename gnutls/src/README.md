src - gnutls
===============

gnutls sample <br/>

## sample code
- basic_tls_client.c <br/>
TLS Client example with X.509 certificate support <br/>
- https_echo_server.c <br/>
HHTPS Echo server with X.509 authentication <br/>
- version.c <br/>
display version <br/>
 

build sample code<br/>
% gcc basic_tls_client.c  `pkg-config --cflags --libs gnutls`
 
run sample code <br/>
Usage: ./a.out  [host] [port] [verify]  <br/>

display as below <br/>
> Conntect to example.com <br/>
> HTTP/1.1 200 OK <br/>


### Reference 
- https://www.gnutls.org/manual/gnutls-guile.html

