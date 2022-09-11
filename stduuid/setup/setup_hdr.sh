#!/bin/bash

# setup for header files
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/stduuid
INC=${ROOT}/include


mkdir ${ROOT}
mkdir ${INC}

cp -R include ${ROOT}
cp -R gsl ${INC}
cp -R catch ${INC}


ls ${INC}


