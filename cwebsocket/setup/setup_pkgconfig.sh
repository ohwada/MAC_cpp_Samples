#!/bin/bash

# setup for pkgconfig
# 2022-10-01 K.OHWADA

ROOT=/usr/local/opt/cwebsocket
PKGCONFIG=${ROOT}/pkgconfig
PCNAME=cwebsocket.pc

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/${PCNAME} /usr/local/lib/pkgconfig/${PCNAME}

ls -la /usr/local/lib/pkgconfig/${PCNAME}

