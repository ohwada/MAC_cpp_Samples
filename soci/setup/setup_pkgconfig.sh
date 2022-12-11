#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

VER=4.0.3
ROOT=/usr/local/Cellar/soci/${VER} 
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

cd ${PKGCONFIG}
pwd

files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    ln -s  ${PKGCONFIG}/${file} /usr/local/lib/pkgconfig/${file}
done

ls -la /usr/local/lib/pkgconfig/soci.pc

