#!/bin/bash

# 2020-07-01 K.OHWADA
# link pkgconfig flie to system area

dir_pkgconfig=/usr/local/Cellar/zlib/1.2.11/lib/pkgconfig

ln -s  ${dir_pkgconfig}/zlib.pc /usr/local/lib/pkgconfig/zlib.pc
