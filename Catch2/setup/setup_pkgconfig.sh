#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/catch2
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/catch2.pc /usr/local/lib/pkgconfig/catch2.pc

ln -s ${PKGCONFIG}/catch2-with-main.pc /usr/local/lib/pkgconfig/catch2-with-main.pc


ls -la /usr/local/lib/pkgconfig/catch2.pc

ls -la /usr/local/lib/pkgconfig/catch2-with-main.pc


