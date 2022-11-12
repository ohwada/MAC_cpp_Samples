#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/json_dto
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/json_dto.pc /usr/local/lib/pkgconfig/json_dto.pc

ls -la /usr/local/lib/pkgconfig/json_dto.pc

