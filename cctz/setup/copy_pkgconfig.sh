#!/bin/bash

# 2020-03-01 K.OHWADA
# copy pkgconfig flies to system area

dir_pkgconfig=/usr/local/Cellar/cctz/2.3/pkgconfig

mkdir ${dir_pkgconfig}

cp pkgconfig/*.pc ${dir_pkgconfig}

ln -s ${dir_pkgconfig}/cctz.pc /usr/local/lib/pkgconfig/cctz.pc

