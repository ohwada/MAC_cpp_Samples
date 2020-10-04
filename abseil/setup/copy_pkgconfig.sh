#!/bin/bash

# 2020-03-01 K.OHWADA
# copy pkgconfig flies to system area

dir_pkgconfig=/usr/local/Cellar/abseil/20200225.2/pkgconfig

mkdir ${dir_pkgconfig}

cp pkgconfig/*.pc ${dir_pkgconfig}

cd pkgconfig
pwd
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file}
done
