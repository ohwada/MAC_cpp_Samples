src = openssl
===============

openssl Sample <br/>

### sample code
- https_client.c <br/>
HTTPS Client <br/>
- https_server.c <br/>
simple HTTPS Server <br/>

- https_hostname_validation.c <br/>
verify host name of server certificate <br/>
- get_server_cert.c <br/>
obtain server SSL certificate <br/>
- show_cert_file.cpp <br/>
 show SSL certificate info from file <br/>
- version.c <br/>
display version <br/>


build code <br/>
% gcc https_client.c `pkg-config --cflags --libs openssl` <br/>

run code  <br/>
Usage: ./a.out  [host] [port] <br/>

display as below <br/>
> Conntect to example.com <br/>
> HTTP/1.1 200 OK <br/>
> \<title\>Example Domain  \</title\> <br/>


### Reference <br/>
- https://github.com/openssl/openssl

