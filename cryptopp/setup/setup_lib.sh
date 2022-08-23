#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/cryptopp

INC=${ROOT}/include
LIB=${ROOT}/lib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}

cp *.h ${INC}
cp libcryptopp.a ${LIB}

ls ${INC}
ls  ${LIB}

