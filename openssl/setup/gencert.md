gencert - openssl
===============

genarate HTTPS Server Certification files by openssl command <br/>


### create a self-signed Certificate Authority

preparation  <br/>
% setup_bin.sh  <br/>
% cd work # your favorite directory  <br/>
% setup_ca.sh  <br/>

(1) generate a private key for CA ( Certificate Authority )
% /usr/local/bin/openssl genrsa -aes256 -out cakey.pem 2048

(2) generate CSR( Certificate Signing Request ) file for CA
hoge ssl
% /usr/local/bin/openssl req -new -key cakey.pem -out cacert.csr

(3) generate a self-signed x509 certificate for CA
% /usr/local/bin/openssl x509 -days 3650 -in cacert.csr -req -signkey cakey.pem -out cacert.pem

(4) settings for CA operation
% mv cakey.pem demoCA/private/cakey.pem
% mv cacert.pem demoCA/cacert.pem


### genarate CA signed Server Certification files

(1) generate a private key for the Server
 % /usr/local/bin/openssl genrsa -aes256 -out server_key.pem 2048

(2) generate a private key without a passphrase
 % /usr/local/bin/openssl rsa -in server_key.pem -out server_nopass_key.pem

(3) generate CSR file for Server
 % /usr/local/bin/openssl req -new -key server_nopass_key.pem -out server.csr

(4) generate CA signed certificate for Server
 % /usr/local/bin/openssl ca -in server.csr -out server_cert.pem -days 365


Reference :  <br/>
- openssl Command Line Utilities <br/>
https://wiki.openssl.org/index.php/Command_Line_Utilities <br/>

