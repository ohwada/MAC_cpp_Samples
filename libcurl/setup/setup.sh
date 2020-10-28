#!/bin/bash

# 2020-07-01 K.OHWADA
# link pkgconfig flie to system area

dir_curl="/usr/local/Cellar/curl/7.73.0"
dir_pkgconfig=${dir_curl}/lib/pkgconfig

# link pkgconfig flie to system area
 ln -s ${dir_pkgconfig}/libcurl.pc /usr/local/lib/pkgconfig/libcurl.pc
