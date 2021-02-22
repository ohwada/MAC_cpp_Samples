keys - openssl
===============

openssl sample <br/>

### Required keys

S/MIME sample code requires the keys <br/>

the email sender needs the following three <br/>

- private key <br/>
- public key certificate issued by CA <br/>
- Root certificate of CA that issued the public key certificate <br/>

the email recipient needs the following two <br/>

- private key <br/>
- public key certificate <br/>
apply Self-signed certificate <br/>

### generate keys

see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/blob/master/openssl/setup/gencert/
