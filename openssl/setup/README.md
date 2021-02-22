setup - openssl
===============

setup for openssl <br/>


### Note
LibreSSL is pre-installed on macOS <br/>
% openssl version <br/>
LibreSSL 2.8.3 <br/>


###  install openssl 
% brew install openssl <br/>
https://formulae.brew.sh/formula/openssl@1.1 <br/>

###  set up for binary command

> % bash setup_bin.sh

> % /usr/local/bin/openssl version
> OpenSSL 1.1.1i  8 Dec 2020

###  set up for library

fix missing openssl files in catalina <br/>
> % bash fix_openssl_catalina.sh	

> % ls -la /usr/local/lib/libssl.dylib
> /usr/local/lib/libssl.dylib -> /usr/local/Cellar/openssl@1.1/1.1.1i/lib/libssl.dylib

### /usr/lib/libssl.dylib 

the library file "libssl.dylib" is pre-installed <br/>

But it doesn't work with this <br/>

for example <br/>

% gcc tcp/echo_client.c  -I/Library/Frameworks/GStreamer.framework/Headers  -L/usr/lib -lssl
> error: linker command failed with exit code 1 <br/>

###  set up for pkgconfig

> % bash setup_pkgconfig.sh

check for pkg-config <br/>
% pkg-config --cflags --libs openssl <br/>
> -I/usr/local/Cellar/openssl@1.1/1.1.1h/include <br/>
> -L/usr/local/Cellar/openssl@1.1/1.1.1h/lib <br/>
> -lssl -lcrypto <br/>

### setup for HTTPS Server

generate HTTPS Server  Cetification <br/>
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/openssl/setup/gencert.md <br/>


Reference :  <br/>
your binary is not an allowed client of /usr/lib/libcrypto.dylib <br/>
https://stackoverflow.com/questions/58446253/xcode-11-ld-error-your-binary-is-not-an-allowed-client-of-usr-lib-libcrypto-dy <br/>

