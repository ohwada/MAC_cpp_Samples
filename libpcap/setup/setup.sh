#!/bin/bash

# 2022-06-01 K.OHWADA
# copy pkgconfig flie to system area

ver=1.10.1
 root=/usr/local/Cellar/libpcap/${ver}
pkgconfig=${root}/lib/pkgconfig

ln -s  ${pkgconfig}/libpcap.pc  /usr/local/lib/pkgconfig/libpcap.pc

ls -la /usr/local/lib/pkgconfig/libpcap.pc
