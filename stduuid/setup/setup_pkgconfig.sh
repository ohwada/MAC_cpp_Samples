#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/stduuid
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/stduuid.pc /usr/local/lib/pkgconfig/stduuid.pc

ls -la /usr/local/lib/pkgconfig/stduuid.pc

