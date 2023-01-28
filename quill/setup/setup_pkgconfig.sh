#!/bin/bash

# 2022-10-01 K.OHWADA
# copy pkgconfig flies to system area

ver=2.5.1
prefix=/usr/local/Cellar/quill/${ver}
dir_pkgconfig=${prefix}/pkgconfig

 ln -s ${dir_pkgconfig}/quill.pc /usr/local/lib/pkgconfig/quill.pc
