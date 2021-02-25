certs - openssl
===============

CA and Server certificates <br/>

 ### CA Root Certificate <br/>

- bundole_ca.pem <br/>

one certificate of major CAs <br/>
download from below <br/>
https://hg.mozilla.org/releases/mozilla-release/raw-file/default/security/nss/lib/ckfw/builtins/certdata.txt <br/>


### Private CA

- hoge_root_cert.pem <br/>
Private Root CA <br/>

- hoge_inter_cert.pem <br/>
Private Intermediate CA <br/>

- hoge_ca_chain_cert.pem <br/>
chain cert for https_client_verify <br/>

% cat hoge_root_cert.pem hoge_inter_cert.pem > hoge_ca_chain_cert.pem <br/>

### Server certificates

- localhost_key.pem <br/>
private key witout passphrase <br/>

- localhost_self_signed_cert.pem <br/>
- localhost_root_signed_cert.pem <br/>
- localhost_inter_signed_cert.pem <br/>


### how to generate ertificates

see below
https://github.com/ohwada/MAC_cpp_Samples/tree/master/openssl/setup/gencert <br/>


### confirm certificate

(confirm the contents of certificate <br/>

% openssl x509 -text -noout -in cert.pem <br/>

