#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/Cellar/libharu/2.4.0
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/libharu.pc /usr/local/lib/pkgconfig/libharu.pc

ls -la /usr/local/lib/pkgconfig/libharu.pc

