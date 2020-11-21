setup - gnutls
===============

setup for gnutls <br/>
genarate server certification files by gnu-certtool command <br/>


### Note
macOS has preinstalled certtool command <br/>
https://opensource.apple.com/source/Security/Security-54/CertTool/CertTool.html <br/>


### genarate Server Certification files
generate server certification files <br/>

(1) prepare template file <br/>

template file format <br/>
- https://www.gnutls.org/manual/html_node/certtool-Invocation.html#Certtool_0027s-template-file-format

(2) generate a private key <br/>
% gnutls-certtool -p --bits 4096 --outfile server.key <br/>

(3)  generate a self-signed certificate <br/>
%  gnutls-certtool -s --hash SHA512 --load-privkey server.key --template server_template.txt --outfile server.crt <br/>


### Reference 
- https://wiki.parabola.nu/Creating_SSL_Certificates
- https://man7.org/linux/man-pages/man1/certtool.1.html

