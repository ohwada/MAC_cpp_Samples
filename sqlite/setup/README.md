setup - sqlite
===============

setup for sqlite <br/>


### Note: 
sqlite is preinstalled on macOS <br/>

binary <br/>
% sqlite3 --version <br/>
3.28.0 2019-04-15 14:49:49 <br/>

header file <br/>
% ls /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/sqlite* <br/>

librariy file <br/>
% ls /usr/lib/libsqlite* <br/>


###  install sqlite
% brew install sqlite <br/>
https://formulae.brew.sh/formula/sqlite <br/>


###  set up for pkg-config
% bash setup.sh <br/>

check for pkg-config <br/>
% pkg-config --cflags --libs sqlite3 <br/>
> -I/usr/local/Cellar/sqlite/3.33.0/include <br/>
> -L/usr/local/Cellar/sqlite/3.33.0/lib <br/>
-lsqlite3 <br/>


### Reference <br/>
- https://sqlite.org/index.html


