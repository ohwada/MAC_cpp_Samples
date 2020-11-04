setup - vmail
===============

setup for vmime <br/>

### requires
-  GNU GCC <br/>
https://formulae.brew.sh/formula/gcc

- CMake  <br/>
https://formulae.brew.sh/formula/cmake

- ICU library or GNU libiconv  <br/>
https://formulae.brew.sh/formula/icu4c

- GNU SASL Library  <br/>
https://formulae.brew.sh/formula/gsasl

- OpenSSL library or the GNU TLS Library  <br/>
https://formulae.brew.sh/formula/gnutls

- jsoncpp

### install
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


### Gmail setting
This sample codes use how to authenticate user with username and password. <br/>
if you use this method with Gmail, <br/>
Allow less secure apps to access your Gmail account <br/>
- https://devanswers.co/allow-less-secure-apps-access-gmail-account/ <br/>

google_acount.png

### Gmail with oauth2
obtain OAuth 2.0 client credentials from the Google API Console. <br/>
and place on Your home directory <br/>

Using OAuth 2.0 to Access Google APIs <br/> 
- https://developers.google.com/identity/protocols/oauth2 <br/>

google_api-console.png

### Reference <br/>
- Developers Guide to VMime <br/>
https://www.vmime.org/public/documentation/book/vmime-book.pdf <br/>


