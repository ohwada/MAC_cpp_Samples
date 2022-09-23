#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/httpparser
INC=${ROOT}/include

mkdir ${ROOT}
mkdir ${INC}

cp -R src/httpparser ${INC}

ls  ${LIB}

