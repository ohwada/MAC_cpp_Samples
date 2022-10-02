#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/sockpp

INC=${ROOT}/include
LIB=${ROOT}/lib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}

cp -R include ${ROOT}
cp build/libsockpp.* ${LIB}

ls ${INC}
ls  ${LIB}

