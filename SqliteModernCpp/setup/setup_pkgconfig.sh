#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA


ROOT=/usr/local/opt/sqlite_modern_cpp
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/sqlite_modern_cpp.pc  /usr/local/lib/pkgconfig/sqlite_modern_cpp.pc

ls -la /usr/local/lib/pkgconfig/sqlite_modern_cpp.pc

