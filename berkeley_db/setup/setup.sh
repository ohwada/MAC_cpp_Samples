#!/bin/bash

# 2021-02-01 K.OHWADA
# copy pkgconfig flies to system area

dir_pkgconfig=/usr/local/Cellar/berkeley-db/18.1.32_1/pkgconfig

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
