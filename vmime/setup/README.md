setup - vmime
===============

setup for vmime <br/>

### Requires

-  GNU GCC <br/>
https://formulae.brew.sh/formula/gcc <br/>

- CMake  <br/>
https://formulae.brew.sh/formula/cmake <br/>

- ICU library or GNU libiconv  <br/>
https://formulae.brew.sh/formula/icu4c <br/>

- GNU SASL Library  <br/>
https://formulae.brew.sh/formula/gsasl <br/>

- OpenSSL library or the GNU TLS Library  <br/>
https://formulae.brew.sh/formula/gnutls <br/>

- jsoncpp <br/>
https://formulae.brew.sh/formula/jsoncpp <br/>


### Install

download sorce files  <br/>
% git clone git://github.com/kisli/vmime  <br/>

build sorce files  <br/>
 % cd vmime <br/>
% mkdir build <br/>
% cd build <br/>
% cmake .. -G "Unix Makefiles" <br/>
% cmake --build . <br/>
% sudo make install <br/>

placed libvmime.1.0.0.dylib and vmime.a in /usr/local/lib

Note: <br/>
when run "brew doctor" <br/>
You get the following warning <br/>
> Unexpected dylibs:
> /usr/local/lib/libvmime.1.0.0.dylib

if You are curious, <br/>
try to change file arrangement <br/>
% bash setup.sh <br/>


### gmail.json

create gmail.json include Your account and Your password <br/>
and place on Your home directory <br/>

template <br/>
gmail.json <br/>
https://github.com/ohwada/MAC_cpp_Samples/blob/master/vmime/setup/gmail.json <br/>

### Gmail setting
This sample codes use how to authenticate user with username and password. <br/>
if you use this method with Gmail, <br/>
Allow less secure apps to access your Gmail account <br/>
- https://devanswers.co/allow-less-secure-apps-access-gmail-account/ <br/>

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/setup/images/google_acount.png" width="300" />


### CertificateVerifier

verify  Server Certificaton <br/>

####  Gmail

download Root Certificaton <br/>
Google Trust Services <br/>
https://pki.goog/repository/ <br/>

####  OCN

download Root Certificaton <br/>
DigiCert Trusted Root Authority Certificates <br/>
https://www.digicert.com/kb/digicert-root-certificates.htm <br/>

####  local server

local server such as postfix on ubuntu <br/>
obtsain Server Certificaton <br/>
place it in Your home directory <br/>


### Gmail with oauth2

obtain OAuth 2.0 client credentials from the Google API Console. <br/>
and place on Your home directory <br/>

Using OAuth 2.0 to Access Google APIs <br/> 
- https://developers.google.com/identity/protocols/oauth2 <br/>

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/setup/images/google_api_console.png" width="300" /> <br/>

### sendmail mode
 Requires : You can use sendmail command <br/>
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/postfix/setup <br/>

### Reference <br/>
- Developers Guide to VMime <br/>
https://www.vmime.org/public/documentation/book/vmime-book.pdf <br/>


