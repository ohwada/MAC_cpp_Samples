setup - zlib
===============

setup for zlib <br/>


### Note: 
zlib is preinstalled on macOS <br/>

header file <br/>
% ls /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/zlib* <br/>

librariy file <br/>
% ls /usr/lib/libz* <br/>




###  install zlib
% brew install zlib <br/>
https://formulae.brew.sh/formula/zlib <br/>


###  set up for pkg-config
% bash setup.sh <br/>

check for pkg-config <br/>
% pkg-config --cflags --libs zlib <br/>
> -I/usr/local/Cellar/zlib/1.2.11/include  <br/>
> -L/usr/local/Cellar/zlib/1.2.11/lib  <br/>
> -lz

