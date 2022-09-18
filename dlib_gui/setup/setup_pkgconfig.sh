#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/dlib_gui
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/dlib_gui.pc /usr/local/lib/pkgconfig/dlib_gui.pc

ls -la /usr/local/lib/pkgconfig/dlib_gui.pc

