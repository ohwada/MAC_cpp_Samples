#!/bin/bash

# setup for header files
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/sqlite_modern_cpp
INC=${ROOT}/include

mkdir ${ROOT}
mkdir ${INC}

 cp -r hdr/* ${INC}

ls ${INC}

