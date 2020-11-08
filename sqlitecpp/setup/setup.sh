#!/bin/bash

# 2020-07-01 K.OHWADA
# change file arrangement

dir_sqlitecpp=/usr/local/opt/sqlitecpp
dir_include=${dir_sqlitecpp}/include
dir_lib=${dir_sqlitecpp}/lib
dir_pkgconfig=${dir_sqlitecpp}/pkgconfig
dir_usr_lib=/usr/local/lib

mkdir ${dir_sqlitecpp}
mkdir ${dir_include}
mkdir ${dir_lib}
mkdir ${dir_pkgconfig}


# move header files
mv /usr/local/include/sqlitecpp ${dir_include}/SQLiteCpp
mv /usr/local/include/sqlite3.h ${dir_include}/sqlite3.h


# move library files
mv /usr/local/lib/libSQLiteCpp.a ${dir_lib}/libSQLiteCpp.a
mv /usr/local/lib/libsqlite3.a ${dir_lib}/ibsqlite3.a

# copy pkgconfig files
cp pkgconfig/sqlitecpp.pc ${dir_pkgconfig}

# link pkgconfig files 
ln -s  ${dir_pkgconfig}/sqlitecpp.pc /usr/local/lib/pkgconfig/sqlitecpp.pc

