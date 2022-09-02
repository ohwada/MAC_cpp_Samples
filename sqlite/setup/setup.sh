#!/bin/bash

# 2022-06-01 K.OHWADA
# link bin flie and pkgconfig flie to system area

ver=3.39.2
root=/usr/local/Cellar/sqlite/${ver}
bin=${root}/bin
pkgconfig=${root}/lib/pkgconfig

ln -s  ${bin}/sqlite3 /usr/local/bin/sqlite3

ln -s  ${pkgconfig}/sqlite3.pc /usr/local/lib/pkgconfig/sqlite3.pc

ls -la  /usr/local/bin/sqlite3

ls -la /usr/local/lib/pkgconfig/sqlite3.pc

