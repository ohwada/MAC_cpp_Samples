#!/bin/bash

# 2020-07-01 K.OHWADA
# link pkgconfig flies to system area

dir_pkgconfig=/usr/local/Cellar/icu4c/67.1/lib/pkgconfig

cd ${dir_pkgconfig}
pwd
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file}
done
