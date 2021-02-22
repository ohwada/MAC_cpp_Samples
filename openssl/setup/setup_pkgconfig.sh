#!/bin/bash

# copy pkgconfig flies to system area
# 2021-02-01 K.OHWADA

 # read conf file
. ./conf.txt


# check directory
mkdir ${dir_pkgconfig}

if [ ! -d ${DIR} ]; then
    echo 'not found dir'
fi

dir_pkgconfig=${DIR}/pkgconfig

# mkdir if not exists
 if [ ! -e ${dir_pkgconfig} ]; then
    mkdir ${dir_pkgconfig}
fi

cd pkgconfig/
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    cp ${file} ${dir_pkgconfig}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file} 
done
