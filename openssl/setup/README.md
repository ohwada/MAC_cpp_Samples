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

fix missing openssl files in catalina <br/>
% bash fix_openssl_catalina.sh <br/>


###  set up for pkgconfig
% bash setup.sh

check for pkg-config <br/>
% pkg-config --cflags --libs openssl <br/>
> -I/usr/local/Cellar/openssl@1.1/1.1.1h/include <br/>
> -L/usr/local/Cellar/openssl@1.1/1.1.1h/lib <br/>
> -lssl -lcrypto <br/>


### /usr/lib/libssl.dylib
the library file "libssl.dylib" is pre-installed <br/>
but You can not use it <br/>

% gcc https_client.c  -I/Library/Frameworks/GStreamer.framework/Headers  -L/usr/lib -lssl <br/>
> ld: library not found for -lssl <br/>

% gcc https_client.c  -I/Library/Frameworks/GStreamer.framework/Headers   -lm /usr/lib/libssl.dylib <br/>
> ld: cannot link directly with dylib/framework, your binary is not an allowed client of /usr/lib/libssl.dylib for architecture x86_64 <br/>


### setup for HTTPS Server
generate HTTPS Server  Cetification files <br/>
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/openssl/setup/gencert.md <br/>


Reference :  <br/>
your binary is not an allowed client of /usr/lib/libcrypto.dylib <br/>
https://stackoverflow.com/questions/58446253/xcode-11-ld-error-your-binary-is-not-an-allowed-client-of-usr-lib-libcrypto-dy <br/>

