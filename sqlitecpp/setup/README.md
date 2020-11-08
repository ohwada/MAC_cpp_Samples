setup - sqlitecpp
===============

setup for sqlitecpp <br/>

### requires
-  sqlite3 <br/>
https://formulae.brew.sh/formula/sqlite <br/>

### install
download sorce files  <br/>
% git clone https://github.com/SRombauts/SQLiteCpp.git <br/>

build sorce files  <br/>
% cd SQLiteCpp <br/>
% mkdir build <br/>
% cd build <br/>
% cmake .. <br/>
% make <br/>
% make install <br/>

placed sqlitecpp.a in /usr/local/lib

Note: <br/>
when run "brew doctor" <br/>
You get the following warning <br/>
> Unexpected static libraries:
> /usr/local/lib/sqlitecpp.a

if You are curious, <br/>
try to change file arrangement <br/>
% bash setup.sh <br/>

check pkgconfig <br/>
% pkg-config --cflags --libs sqlitecpp <br/>
> -I/usr/local/opt/sqlitecpp/include <br/>
> -I/usr/local/Cellar/sqlite/3.33.0/include <br/>
> -L/usr/local/opt/sqlitecpp/lib <br/>
> -L/usr/local/Cellar/sqlite/3.33.0/lib <br/>
> -lsqlitecpp -lsqlite3 <br/>


### Reference <br/>
- https://github.com/SRombauts/SQLiteCpp <br/>
