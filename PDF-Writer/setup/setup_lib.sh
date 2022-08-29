#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/PDFWriter
INC=${ROOT}/include
LIB=${ROOT}/lib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${INC}/PDFWriter
mkdir ${LIB}

cp PDFWriter/*.h ${INC}/PDFWriter/
cp build/PDFWriter/libPDFWriter.a ${LIB}
cp build/LibAesgm/libLibAesgm.a  ${LIB}

ls ${INC}/PDFWriter/
ls  ${LIB}
