gencert - openssl
===============

setup for openssl <br/>
create HTTPS Server Certificate by openssl command <br/>


### create  Self-signed Server Certificate

(1) generate a private key for the Server <br/>

 % openssl genrsa -aes256 -out server_key.pem 2048 <br/>

(2) generate a private key without a passphrase <br/>

 % openssl rsa -in server_key.pem -out server_nopass_key.pem <br/>

You need to enter the passphrase when starting the server <br/>
Allows to start the server without passphrase <br/>

(3) generate Self-signed certificate <br/>

% openssl req -x509 -new -key privatekey.pem -out cert.pem -days 356 <br/>


enter the following items <br/>

- countryName <br/>
- stateOrProvinceName <br/>
- localityName <br/>
- organizationName	 <br/>
- organizationalUnitName <br/>
- emailAddress <br/>
- challengePassword <br/>

- commonName <br/>
enter Server Name <br/>
FQDN is desirable <br/>
for local net, match with etc/hosts <br/>
can be "localhost" <br/>

(4) confirm the contents of certificate <br/>

% openssl x509 -text -noout -in cert.pem 

(5) confirm the purpose of certificate

% openssl x509 -purpose -in cert.pem -noout


## create a Private CA Signed Server Certificate

### create Private Root CA

(1) create a directory structure to operate the Root CA <br/>

% cd work # your favorite directory  <br/>
% bash setup_root_ca.sh  <br/>

(2) generate a private key for Root  CA  <br/>

% openssl genrsa -aes256 -out cakey.pem 2048 <br/>

(3) generate CSR for Root CA <br/>

% openssl req -new -key cakey.pem -out cacert.csr <br/>

(4) confirm CSR <br/>

% openssl req -noout -text -in cacert.csr <br/> 

(4) Root CA signs CSR <br/>

% openssl x509 -req  -signkey cakey.pem -in cacert.csr -out cacert.pem -days 3650 <br/>

(5) confirm the contents of certificate <br/>

% openssl x509 -text -noout -in cacert.pem 

(6) confirm the purpose of certificate

% openssl x509 -purpose -in cacert.pem -noout

(7) settings for CA operation <br/>
% cp cakey.pem demoCA/private/ <br/>
% cp cacert.pem demoCA/ <br/>

(8) macOS : install  the CA Certificate to macOS Keychainsettings  <br/>

% sudo security add-trusted-cert -d -r trustRoot -k "/Library/Keychains/System.keychain" cacert.pem


### create Private Intermediate CA

(1) create a directory structure to operate the Intermediate CA <br/>

% cd work # your favorite directory  <br/>
% setup_inter_ca.sh  <br/>

(2) generate a private key for the  Intermediate CA <br/>

 % openssl genrsa -aes256 -out inter_key.pem 2048 <br/>

(3) generate CSR for  Intermediate  CA <br/>

 % openssl req -new -key inter_key.pem -out inter.csr <br/>

(4) confirm CSR <br/>

% openssl req -noout -text -in inter.csr <br/> 

(5) Root CA signs CSR with sign_inter.cnf <br/>

%  openssl x509 -req -extfile sign_inter.cnf  -in inter.csr -out inter_cert.pem -extensions v3_ca -days 3650 

(6) confirm the contents of certificate <br/>

% openssl x509 -text -noout -in inter_cert.pem 

(7) confirm the purpose of certificate

% openssl x509 -purpose -in inter_cert.pem -noout

 (8) verify certificate <br/>

% openssl verify -CAfile cacert.pem inter_cert.pem

(9) settings for CA operation <br/>

% cp inter_key.pem interCA/private/ <br/>
% cp inter_cert.pem interCA/ <br/>


### genarate CA signed Server Certificate

(1) generate a private key for the Server <br/>

 % openssl genrsa -aes256 -out server_key.pem 2048 <br/>

(2) generate a private key without a passphrase <br/>

 % openssl rsa -in server_key.pem -out server_nopass_key.pem <br/>

(3) generate CSR with SAN <br/>

(3-1) create  configuration file　<br/>

refer to sample_san.cnf <br/>

(3-2) generate CSR with  -config <br/>
% openssl req -new -config san.cnf -key server_key.pem -out server.csr

(4) confirm CSR <br/>

% openssl req -noout -text -in server.csr 

(5) Intermediate CA signs CSR <br/>

 % openssl ca  -config inter_ca.cnf  -in server.csr -out server_cert.pem -days 397 <br/>

the maximum allowed lifetimes is 397 days. <br/>

(6) confirm the contents of certificate <br/>

% openssl x509 -text -noout -in server_cert.pem 

(7) confirm the purpose of certificate

% openssl x509 -purpose -in server_cert.pem -noout

(8) verify certificate <br/>

(8-1) create a CA certificate chain

% cat cacert.pem inter_cert.pem > ca_chain_cert.pem

(8-2) verify certificate with CAfile <br/>

% openssl verify -CAfile ca_chain_cert.pem server_cert.pem


### Reference 

- openssl Command Line Utilities <br/>
https://wiki.openssl.org/index.php/Command_Line_Utilities <br/>

- how-to-create-a-self-signed-certificate-with-openssl <br/>
https://stackoverflow.com/questions/10175812/how-to-create-a-self-signed-certificate-with-openssl/43860138#43860138 <br/>

- SSL Certificate Maximum Duration Set To 825 Days <br/>
https://www.ssl.com/blogs/ssl-certificate-maximum-duration-825-days/ <br/>

- Chrome Deprecates Subject CN Matching <br/>
https://textslashplain.com/2017/03/10/chrome-deprecates-subject-cn-matching/ <br/>

- Subject Alternative Name not present in certificate
https://stackoverflow.com/questions/30977264/subject-alternative-name-not-present-in-certificate

- How to Create Your Own SSL Certificate Authority for Local HTTPS Development <br/>
https://deliciousbrains.com/ssl-certificate-authority-for-local-https-development/ <br/>

- Any Purpose CA : Yes  <br/>
http://openssl.6102.n7.nabble.com/quot-critical-CA-FALSE-quot-but-quot-Any-Purpose-CA-Yes-quot-td29933.html  <br/>

- About upcoming limits on trusted certificates <br/>
https://support.apple.com/en-us/HT211025 <br/>

- プライベートルート証明書・中間証明書・サーバ証明書の作り方 <br/>
 https://http2.try-and-test.net/openssl_simple_ca.html <br/>

- SAN(Subject Alternative Name) のオレオレ証明書 <br/>
https://qiita.com/nis_nagaid_1984/items/b8f87d41ea108d47af61 <br/>

