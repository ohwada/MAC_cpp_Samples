setup - boost_beast
===============

setup for  boost beast <br/>

###  install boost beast 
boost beast is a part of boost library <br/>
see boost <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/boost <br/>


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
https://hg.mozilla.org/releases/mozilla-release/raw-file/default/security/nss/lib/ckfw/builtins/certdata.txt <br/>

#### setup for HTTPS Server
generate Server Cetification file <br/>
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/blob/master/openssl/setup/gencert.md <br/>


### Reference <br/>
- https://www.boost.org/



