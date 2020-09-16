bio - openssl
===============

openssl Sample <br/>
connect Google using BIO_new_connect <br/>


### bio_new_connect.c 
connect Google using BIO_new_connect <br/>


build code <br/>
% cmake . <br/>
% make <br/>

run code  <br/>
 ./bio_new <br/>

display as below <br/>
conected: www.google.com:443 <br/>
bio = 34405800 <br/>


### TODO
OPENSSL_INCLUDE_DIR <br/>
obtained by find_package was <br/>
/Library/Frameworks/GStreamer.framework/Headers<br/>

expected <br/>
/usr/local/Cellar/openssl@1.1/1.1.1g/include <br/>

