#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/dlib_gui
INC=${ROOT}/include
LIB=${ROOT}/lib

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}

cp -R dlib/ ${INC}
cp build/dlib/libdlib.a ${LIB}/libdlibgui.a


ls ${INC}
ls  ${LIB}


