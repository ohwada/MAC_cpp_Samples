gnutls
===============

gnutls sample <br/>

GnuTLS : <br/>
GnuTLS is a secure communications library implementing the SSL, TLS and DTLS protocols and technologies around them. <br/>
https://www.gnutls.org/ <br/>


###  install GnuTLS
% brew instal gnutls <br/>
https://formulae.brew.sh/formula/gnutls <br/>


### setup for HTTS Server
generate Server Certification files </br>
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/gnutls/setup <br/>

## sample code
- basic_tls_client.c <br/>
TLS Client example with X.509 certificate support <br/>
- https_echo_server.c <br/>
HHTPS Echo Server with X.509 authentication <br/>
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

