gencert - openssl
===============

genarate HTTPS Server Certification files by openssl command <br/>




### genarate HTTPS Server Certification files
generate private key file and X509 cetification file <br/>

(1) generate private.key <br/>
% openssl genrsa 2024 > server.key <br/>

(2) generate csr (Certificate Signing Request) <br/>
% openssl req -new -key server.key > server.csr <br/>

(3) generate X509 cetification file <br/>
% openssl x509 -req -days 365 -signkey server.key < server.csr > server.crt <br/>

Reference :  <br/>
- openssl Command Line Utilities <br/>
https://wiki.openssl.org/index.php/Command_Line_Utilities <br/>

