#!/bin/bash

# copy pkgconfig flies to system area
# 2022-06-01 K.OHWADA

 # read conf file
. ./conf.txt

dir_pkgconfig=${DIR}/lib/pkgconfig/

cd ${dir_pkgconfig}
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    ln -s ${dir_pkgconfig}${file} /usr/local/lib/pkgconfig/${file} 
done
