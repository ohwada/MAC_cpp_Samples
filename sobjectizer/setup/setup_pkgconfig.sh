#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/sobjectizer
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/sobjectizer.pc /usr/local/lib/pkgconfig/sobjectizer.pc

ls -la /usr/local/lib/pkgconfig/sobjectizer.pc


