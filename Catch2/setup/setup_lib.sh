#!/bin/bash

# setup for header files and lib file
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/catch2

INC=${ROOT}/include
LIB=${ROOT}/lib
INC_CATCH2=${INC}/catch2

mkdir ${ROOT}
mkdir ${INC}
mkdir ${LIB}
mkdir ${INC_CATCH2}

cp build/src/libCatch2.a ${LIB}
cp build/src/libCatch2Main.a ${LIB}

cp build/generated-includes/catch2/catch_user_config.hpp ${INC_CATCH2}

cd src

cp catch2/*.hpp ${INC_CATCH2}

# get all sub directories
array=($(find catch2 -type d))
for value in ${array[@]}; do
    echo ${value}
    CHILD=${INC}/${value}
    echo ${CHILD}
    mkdir ${CHILD}
    cp ${value}/*.hpp ${CHILD}
done


ls ${INC}
ls ${INC_CATCH2}
ls  ${LIB}

