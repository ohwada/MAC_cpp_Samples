#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/facil

INC=${ROOT}/include
LIB=${ROOT}/lib


mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}


cp lib/facil/*.h  ${INC}
cp lib/facil/*/*.h  ${INC}

cp build/libfacil.io.a ${LIB}

ls ${INC}
ls  ${LIB}

