keys - openssl
===============

openssl sample <br/>
private key and public key certificate <br/>

### how to generate keys

generate private key <br/>
% openssl genrsa 1024 > privatekey.pem <br/>

generate public key certificate <br/>
% openssl req -x509 -new -key privatekey.pem -out cert.pem -days 356 <br/>

