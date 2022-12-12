#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

VER=3.3.0_1
ROOT=/usr/local/Cellar/mysql++/${VER}
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/mysqlpp.pc /usr/local/lib/pkgconfig/mysqlpp.pc

ls -la /usr/local/lib/pkgconfig/mysqlpp.pc

