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

ln -s ${LIB}/libpngwriter.a /usr/local/lib/libpngwriter.a

ls ${INC}
ls  ${LIB}

ls -la /usr/local/lib/libpngwriter.a
