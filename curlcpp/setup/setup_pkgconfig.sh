#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/curlcpp
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/curlcpp.pc /usr/local/lib/pkgconfig/curlcpp.pc

ls -la /usr/local/lib/pkgconfig/curlcpp.pc

