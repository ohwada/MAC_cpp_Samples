#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/ZipLib
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/ziplib.pc /usr/local/lib/pkgconfig/ziplib.pc

ls -la /usr/local/lib/pkgconfig/ziplib.pc

