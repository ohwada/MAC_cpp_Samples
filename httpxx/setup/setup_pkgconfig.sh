#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/httpxx
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/httpxx.pc /usr/local/lib/pkgconfig/httpxx.pc

ls -la /usr/local/lib/pkgconfig/httpxx.pc

