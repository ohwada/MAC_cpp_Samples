#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/soci
PKGCONFIG=${ROOT}/pkgconfig
PCNAME=soci_mysql.pc

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/${PCNAME} /usr/local/lib/pkgconfig/${PCNAME}

ls -la /usr/local/lib/pkgconfig/${PCNAME}

