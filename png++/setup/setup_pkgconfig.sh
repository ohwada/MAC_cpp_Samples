#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/Cellar/png++/0.2.10
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/pngpp.pc /usr/local/lib/pkgconfig/pngpp.pc

ls -la /usr/local/lib/pkgconfig/pngpp.pc

