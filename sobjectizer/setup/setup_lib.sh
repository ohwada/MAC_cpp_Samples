#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/sobjectizer

INC=${ROOT}/include
LIB=${ROOT}/lib
INC_SO5=${INC}/so_5

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}
mkdir ${INC_SO5}

cp dev/build/so_5/libso_s.5.7.4.2.a ${LIB}
cp dev/build/so_5/libso.5.7.4.2.dylib ${LIB}

ln -s ${LIB}/libso_s.5.7.4.2.a /usr/local/lib/libso_s.5.7.4.2.a
ln -s ${LIB}/libso.5.7.4.2.dylib /usr/local/lib/libso.5.7.4.2.dylib

cd dev/

cp so_5/*.hpp ${INC_SO5}

# get all sub directories
array=($(find so_5 -type d))
for value in ${array[@]}; do
    echo ${value}
    CHILD=${INC}/${value}
    echo ${CHILD}
    mkdir ${CHILD}
    cp ${value}/*.hpp ${CHILD}
done

ls ${INC}
ls ${INC_SO5}/*
ls  ${LIB}

ls -la /usr/local/lib/libso* | grep 5.7

