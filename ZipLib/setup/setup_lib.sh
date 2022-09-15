#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/ZipLib
INC=${ROOT}/include
LIB=${ROOT}/lib
DETAIL=${INC}/detail
INC_EXTLIBS=${INC}/extlibs
INC_BZIP2=${INC_EXTLIBS}/bzip2
INC_LZMA=${INC_EXTLIBS}/lzma
INC_ZLIB=${INC_EXTLIBS}/zlib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}
mkdir ${DETAIL}
mkdir ${INC_EXTLIBS}
mkdir ${INC_BZIP2}
mkdir ${INC_LZMA}
mkdir ${INC_ZLIB}


# header
cp *.h ${INC}
cp -R methods ${INC}
cp -R streams ${INC}
cp -R utils ${INC}
cp -R compression ${INC}
cp detail/*.h ${DETAIL}
cp extlibs/bzip2/*.h ${INC_BZIP2}
cp extlibs/lzma/*.h ${INC_LZMA}
cp extlibs/zlib/*.h ${INC_ZLIB}


# lib
cp build/libZipLib.a ${LIB}
cp build/extlibs/bzip2/libbzip2.a ${LIB}
cp build/extlibs/lzma/liblzma.a ${LIB}
cp build/extlibs/zlib/libzlib.a ${LIB}


ls ${INC}
ls  ${LIB}
