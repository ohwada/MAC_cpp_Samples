#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

VER=0.3.21
ROOT=/usr/local/Cellar/openblas/${VER}
PKGCONFIG=${ROOT}/lib/pkgconfig

ln -s ${PKGCONFIG}/openblas.pc  /usr/local/lib/pkgconfig/openblas.pc

ls -la /usr/local/lib/pkgconfig/openblas.pc

