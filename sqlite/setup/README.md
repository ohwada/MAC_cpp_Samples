setup - sqlite
===============

setup for sqlite  


### Note: 
sqlite is preinstalled on macOS  

binary  
% sqlite3 --version  
3.28.0 2019-04-15 14:49:49  

header file  
% ls /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/sqlite*  

librariy file  
% ls /usr/lib/libsqlite*  


###  install sqlite
% brew install sqlite   
https://formulae.brew.sh/formula/sqlite   


###  set up for pkg-config  
% bash setup.sh   

check for pkg-config   
% pkg-config --cflags --libs sqlite3   
> -I/usr/local/Cellar/sqlite/3.33.0/include   
> -L/usr/local/Cellar/sqlite/3.33.0/lib   
-lsqlite3   


