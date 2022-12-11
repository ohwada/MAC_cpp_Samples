#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/soci

INC=${ROOT}/include
LIB=${ROOT}/lib

LIBNAME1=libsoci_core.a
LIBNAME2=libsoci_mysql.a


mkdir ${ROOT}
mkdir ${LIB}

cp -R include ${ROOT}

cp build/lib/${LIBNAME1}  ${LIB}
cp build/lib/${LIBNAME2}  ${LIB}


ls ${INC}
ls  ${LIB}

