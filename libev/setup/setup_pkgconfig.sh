#!/bin/bash

# 2022-06-01 K.OHWADA
# copy pkgconfig flies to system area

ver=4.33
prefix=/usr/local/Cellar/libev/${ver}
dir_pkgconfig=${prefix}/pkgconfig

mkdir ${dir_pkgconfig}

# copy and link pkgconfig
 cp pkgconfig/*.pc  ${dir_pkgconfig}

 ln -s ${dir_pkgconfig}/libev.pc /usr/local/lib/pkgconfig/libev.pc

ls -la /usr/local/lib/pkgconfig/libev.pc

