#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/httpxx

INC=${ROOT}/include
LIB=${ROOT}/lib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}

cp -R include ${ROOT}
cp bin/libhttpxx.* ${LIB}

ln -s ${LIB}/libhttpxx.a /usr/local/lib/libhttpxx.a

ls ${INC}
ls  ${LIB}

ls -la /usr/local/lib/libhttpxx.a
