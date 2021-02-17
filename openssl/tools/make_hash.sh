#!/bin/bash

# 2021-02-01 K.OHWADA

# and a symbolic link to the CA certificate

files=`ls -1 *.pem`
for file in ${files}
do
    echo ${file}
    hash=`openssl x509 -hash -noout -in ${file}`
    echo ${hash}
    ln -s ${file} "${hash}.0"
done

