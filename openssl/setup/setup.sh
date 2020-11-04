#!/bin/bash

# 2020-07-01 K.OHWADA
# copy pkgconfig flies to system area

dir_pkgconfig=/usr/local/Cellar/openssl@1.1/1.1.1h/pkgconfig

mkdir ${dir_pkgconfig}
cd pkgconfig/
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    cp ${file} ${dir_pkgconfig}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file} 
done
