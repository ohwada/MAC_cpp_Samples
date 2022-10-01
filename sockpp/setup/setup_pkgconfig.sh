#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/sockpp
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/sockpp.pc /usr/local/lib/pkgconfig/sockpp.pc

ls -la /usr/local/lib/pkgconfig/sockpp.pc

