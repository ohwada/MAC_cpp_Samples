#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/httpparser
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/httpparser.pc /usr/local/lib/pkgconfig/httpparser.pc

ls -la /usr/local/lib/pkgconfig/httpparser.pc

