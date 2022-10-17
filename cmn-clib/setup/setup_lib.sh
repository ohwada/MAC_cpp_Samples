#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/cmn-clib

INC=${ROOT}/include
LIB=${ROOT}/lib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}

cp -r inc/* ${INC}
cp build/libcmn-clib.a ${LIB}

ls ${INC}
ls  ${LIB}

