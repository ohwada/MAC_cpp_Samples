setup - cctz
===============

cctz : <br/>
C++ library for translating between absolute and civil times <br/>
https://github.com/google/cctz <br/>


###  install cctz
% brew install cctz <br/>
https://formulae.brew.sh/formula/cctz <br/>


###  set up for pkg-config
% bash copy_pkgconfig.sh <br/>

check for pkg-config <br/>
% pkg-config --cflags --libs cctz <br/>
-I/usr/local/Cellar/cctz/2.3/include -L/usr/local/Cellar/cctz/2.3/lib -lcctz <br/>

### Reference <br/>
- https://github.com/google/cctz <br/>

