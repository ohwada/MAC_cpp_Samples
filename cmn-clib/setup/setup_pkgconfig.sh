#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/cmn-clib
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/cmn-clib.pc /usr/local/lib/pkgconfig/cmn-clib.pc

ls -la /usr/local/lib/pkgconfig/cmn-clib.pc

