#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/nodejs_http_parser

INC=${ROOT}/include
LIB=${ROOT}/lib

VER=2.9.4
LIBNAME=libhttp_parser.${VER}

UNAME=`uname -s | tr "[A-Z]" "[a-z]"`

echo ${UNAME}

if [ ${UNAME} = "darwin" ]; then
TARGET=${LIBNAME}.dylib
else
TARGET=${LIBNAME}.so
fi

echo ${TARGET}

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}

cp http_parser.h ${INC}
cp ${TARGET} ${LIB}

ln -s ${LIB}/${TARGET} /usr/local/lib/${TARGET}

ls ${INC}
ls  ${LIB}

ls -la /usr/local/lib/${TARGET}
