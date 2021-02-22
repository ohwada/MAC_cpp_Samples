#!/bin/bash

# setup for bin command
# 2021-02-01 K.OHWADA

# read conf file
. ./conf.txt

echo ${DIR}

# check directory
if [ ! -d ${DIR} ]; then
    echo 'not found dir'
fi


dir_ssl_bin=${DIR}/bin

 ln -s  ${dir_ssl_bin}/openssl /usr/local/bin/openssl

/usr/local/bin/openssl version
