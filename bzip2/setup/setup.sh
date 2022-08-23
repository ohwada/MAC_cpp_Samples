#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/bzip2
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/bzip2.pc /usr/local/lib/pkgconfig/bzip2.pc

ls -la /usr/local/lib/pkgconfig/bzip2.pc

