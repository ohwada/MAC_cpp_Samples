#!/bin/bash

# 2020-07-01 K.OHWADA
# copy pkgconfig flies to system area

dir_pkgconfig=/usr/local/Cellar/openssl@1.1/1.1.1g/pkgconfig

mkdir ${dir_pkgconfig}

cp pkgconfig/*.pc ${dir_pkgconfig}

ln -s ${dir_pkgconfig}/libssl.pc /usr/local/lib/pkgconfig/libssl.pc 
ln -s ${dir_pkgconfig}/libcrypto.pc /usr/local/lib/pkgconfig/libcrypto.pc
ln -s ${dir_pkgconfig}/openssl.pc /usr/local/lib/pkgconfig/openssl.pc


