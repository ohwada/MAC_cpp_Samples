verify_cert - openssl
===============

openssl Sample <br/>
verify X509 certificate <br/>

Feature equivalent to the command below <br/>
openssl verify [-CApath directory] [-CAfile file] certificates <br/>
https://www.openssl.org/docs/man1.0.2/man1/openssl-verify.html <br/>


## setup


### certificate to verify

get certificate from server <br/>
% openssl s_client -connect host:port <br/>

try get_certs.c <br/>

### trusted certificates 

get trusted certificates from CA web site <br/>

for example <br/>
DigiCert Trusted Root Authority Certificates <br/>
https://www.digicert.com/kb/digicert-root-certificates.htm <br/>

make hashed form <br/>
The certificates in the directory must be in hashed form, <br/>
https://www.openssl.org/docs/man1.1.1/man3/X509_STORE_load_locations.html <br/>

% bash make_hash.sh <br/>


### sample code
- verift localhost.c <br/>
verify localhost cert <br/>
- verify_example_org.c <br/>
verify www.example.org cert <br/>


build code <br/>
% gcc verify_localhost.c  `pkg-config --cflags --libs openssl` <br/>

run code  <br/>
Usage: ./a.out  [cert] [cacert] 
Usage: ./a.out <br/>

display as below <br/>
> cert: certs/localhost_cert.pem <br/>
> commonName                = localhost <br/>

> Verification successfull 

### Reference <br/>
- https://github.com/openssl/openssl

