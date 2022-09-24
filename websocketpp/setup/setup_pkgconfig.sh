#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

VER=0.8.2
ROOT=/usr/local/Cellar/websocketpp/${VER}

PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/websocketpp.pc /usr/local/lib/pkgconfig/websocketpp.pc

ls -la /usr/local/lib/pkgconfig/websocketpp.pc

