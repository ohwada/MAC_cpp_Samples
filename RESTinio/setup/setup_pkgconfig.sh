#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/restinio
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/restinio.pc /usr/local/lib/pkgconfig/restinio.pc

ls -la /usr/local/lib/pkgconfig/restinio.pc


