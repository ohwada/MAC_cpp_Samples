bio - openssl
===============

openssl Sample <br/>
sample for BIO method <br/>


### sample code
- bio_new_connect.c <br/>
connect HTTP server using BIO_new_connect <br/>
- bio_new_ssl_connect.c <br/>
connect HTTPS srver using BIO_new_ssl_connect <br/>


build code <br/>
% cmake . <br/>
% make <br/>

run code  <br/>
 ./bio_new <br/>

display as below <br/>
> conected: example.com:80  <br/>
> bio = 34405800 <br/>


### TODO
OPENSSL_INCLUDE_DIR <br/>
obtained by find_package was <br/>
/Library/Frameworks/GStreamer.framework/Headers<br/>

expected <br/>
/usr/local/Cellar/openssl@1.1/1.1.1h/include <br/>

