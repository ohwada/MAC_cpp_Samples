#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/nodejs_http_parser
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/nodejs_http_parser.pc /usr/local/lib/pkgconfig/nodejs_http_parser.pc

ls -la /usr/local/lib/pkgconfig/nodejs_http_parser.pc


