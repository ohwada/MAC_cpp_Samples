#!/bin/bash

# 2021-02-01 K.OHWADA
# convert format der to pem

files=`ls -1 *.der`
for file in ${files}
do
    echo ${file}
    openssl x509 -inform der  -outform pem  -in ${file} -out ${file}.pem
done

