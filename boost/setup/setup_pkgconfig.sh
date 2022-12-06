#!/bin/bash

# 2022-06-01 K.OHWADA
# copy pkgconfig flies to system area

ver=1.80.0
prefix=/usr/local/Cellar/boost/${ver}
dir_pkgconfig=${prefix}/pkgconfig

mkdir ${dir_pkgconfig}

# copy and link pkgconfig
cd pkgconfig
pwd
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    cp ${file} ${dir_pkgconfig}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file}
done

