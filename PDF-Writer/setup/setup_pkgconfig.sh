#!/bin/bash

# setup for pkgconfig
# 2022-06-01 K.OHWADA

ROOT=/usr/local/opt/PDFWriter
PKGCONFIG=${ROOT}/pkgconfig

mkdir ${PKGCONFIG}

cp pkgconfig/*.pc ${PKGCONFIG}

ln -s ${PKGCONFIG}/pdfwriter.pc /usr/local/lib/pkgconfig/pdfwriter.pc

ls -la /usr/local/lib/pkgconfig/pdfwriter.pc

