#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/pngwriter
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/pngwriter.pc /usr/local/lib/pkgconfig/pngwriter.pc

ls -la /usr/local/lib/pkgconfig/pngwriter.pc

