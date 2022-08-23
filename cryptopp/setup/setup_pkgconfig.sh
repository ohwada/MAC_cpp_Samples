#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/cryptopp
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/cryptopp.pc /usr/local/lib/pkgconfig/cryptopp.pc

ls -la /usr/local/lib/pkgconfig/cryptopp.pc

