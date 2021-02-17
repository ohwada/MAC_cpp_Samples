#!/bin/bash

# copy pkgconfig flies to system area
# 2020-07-01 K.OHWADA

ssl_ver=1.1.1i
dir_pkgconfig=/usr/local/Cellar/openssl@1.1/${ssl_ver}/pkgconfig

mkdir ${dir_pkgconfig}
cd pkgconfig/
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    cp ${file} ${dir_pkgconfig}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file} 
done
