#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/restinio

INC=${ROOT}/include
LIB=${ROOT}/lib


mkdir ${ROOT}
mkdir ${INC}


cd dev

# get all sub directories
array=($(find restinio -type d))
for value in ${array[@]}; do
    echo ${value}
    CHILD=${INC}/${value}
    #echo ${CHILD}
    #mkdir ${CHILD}
    #cp ${value}/*.hpp ${CHILD}
done

 cp restinio/impl/*.ipp ${INC}/restinio/impl
cp restinio/utils/*.ipp ${INC}/restinio/utils

ls ${INC}


