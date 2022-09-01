#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/ZipLib
INC=${ROOT}/include
LIB=${ROOT}/lib
DETAIL=${INC}/detail
EXTLIBS=${INC}/extlibs
BZIP2=${EXTLIBS}/bzip2
LZMA=${EXTLIBS}/lzma
ZLIB=${EXTLIBS}/zlib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}
mkdir ${DETAIL}
mkdir ${EXTLIBS}
mkdir ${BZIP2}
mkdir ${LZMA}
mkdir ${ZLIB}


# header
cp *.h ${INC}
cp -R methods ${INC}
cp -R streams ${INC}
cp -R utils ${INC}
cp -R compression ${INC}
cp detail/*.h ${DETAIL}
cp extlibs/bzip2/*.h ${BZIP2}
cp extlibs/lzma/*.h ${LZMA}
cp extlibs/zlib/*.h ${ZLIB}


# lib
cp build/libZipLib.a ${LIB}
cp build/extlibs/bzip2/libbzip2.a ${LIB}
cp build/extlibs/lzma/liblzma.a ${LIB}
cp build/extlibs/zlib/libzlib.a ${LIB}


ls ${INC}
ls  ${LIB}
