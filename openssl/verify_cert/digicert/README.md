digicert - openssl
===============

root CA for www.example.org <br/>

The files in this directory are downloaded from the below <br/>

DigiCert Trusted Root Authority Certificates <br/>
https://www.digicert.com/kb/digicert-root-certificates.htm <br/>

### Note
The certificates in the directory must be in hashed form, <br/>
X509_STORE_add_cert  <br/>
https://www.openssl.org/docs/man1.1.1/man3/X509_STORE_load_locations.html  <br/>

The certificates should have names of the form: hash.0 or have symbolic links to them of this form <br/>
openssl-verify <br/>
https://www.openssl.org/docs/man1.0.2/man1/openssl-verify.html <br/>

make hashed form  <br/>
try make_hash.sh  <br/>
