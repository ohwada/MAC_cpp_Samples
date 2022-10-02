#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/libzippp
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/libzippp.pc /usr/local/lib/pkgconfig/libzippp.pc

ls -la /usr/local/lib/pkgconfig/libzippp.pc

