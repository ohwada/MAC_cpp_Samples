#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

VER=8.0.30
ROOT=/usr/local/Cellar/mysql-connector-c++/${VER}

PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/mysqlcppconn.pc /usr/local/lib/pkgconfig/mysqlcppconn.pc

ls -la /usr/local/lib/pkgconfig/mysqlcppconn.pc

