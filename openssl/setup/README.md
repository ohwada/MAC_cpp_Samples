setup - openssl
===============

setup for openssl <br/>


###  install openssl 
% brew install openssl <br/>
https://formulae.brew.sh/formula/openssl@1.1 <br/>

### Note
LibreSSL is pre-installed on macOS <br/>
% openssl version <br/>
LibreSSL 2.8.3 <br/>

fix missing openssl files in catalina <br/>
% bash fix_openssl_catalina.sh

###  set up for pkgconfig
% bash copy_pkgconfig.sh

check for pkg-config <br/>
% pkg-config --cflags --libs libssl <br/>
display as below <br/>
-I/usr/local/Cellar/openssl@1.1/1.1.1g//include -L/usr/local/Cellar/openssl@1.1/1.1.1g//lib -lssl


