#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/pngwriter
INC=${ROOT}/include
LIB=${ROOT}/lib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}

cp src/*.h ${INC}
cp lib/libpngwriter.a ${LIB}

ls ${INC}
ls  ${LIB}
