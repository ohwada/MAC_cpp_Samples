setup - cpp_httplib
===============

setup for cpp_httplib <br/>

###  install cpp_httplib
cpp_httplib is header only library  <br/>
Just include "httplib.h" file in your code <br/>
https://github.com/yhirose/cpp-httplib/blob/master/httplib.h <br/>

### setup for HTTP Server
prepare document root directory like www  <br/>
place index html file  <br/>
and files that client can access like image file baboon.png, etc  <br/>

### setup for HTTPS Client and Server

#### Library required <br/>
- openssl <br/>
https://formulae.brew.sh/formula/openssl@1.1 <br/>

#### setup for HTTPS Client
 prepare CA ( Certification Authority ) file <br/>
download from below <br/>
https://hg.mozilla.org/releases/mozilla-release/raw-file/default/security/nss/lib/ckfw/builtins/certdata.txt <br/>

#### setup for HTTPS Server
generate Server Cetification file <br/>
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/blob/master/openssl/setup/gencert/ <br/>


### Reference <br/>
- https://github.com/yhirose/cpp-httplib 

