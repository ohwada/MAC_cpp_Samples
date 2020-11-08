#!/bin/bash

# 2020-07-01 K.OHWADA
# link pkgconfig flie to system area

dir_pkgconfig=/usr/local/Cellar/sqlite/3.33.0/lib/pkgconfig

ln -s  ${dir_pkgconfig}/sqlite3.pc /usr/local/lib/pkgconfig/sqlite3.pc
