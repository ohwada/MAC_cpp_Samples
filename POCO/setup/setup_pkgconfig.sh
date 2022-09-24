#!/bin/bash

# 2020-07-01 K.OHWADA
# copy pkgconfig flie to system area

ver=1.12.1
root=/usr/local/Cellar/poco/${ver}
pkgconfig=${root}/pkgconfig

mkdir ${pkgconfig}

cp pkgconfig/*.pc ${pkgconfig}

ln -s  ${pkgconfig}/poco.pc  /usr/local/lib/pkgconfig/poco.pc

