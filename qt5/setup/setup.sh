#!/bin/bash

# setup.sh
# link qmake and pkgconfig flies to system area
# 2022-06-01 K.OHWADA


dir_qt5=/usr/local/Cellar/qt@5/5.15.3/
echo ${dir_qt5}

dir_pkgconfig=${dir_qt5}lib/pkgconfig/
echo ${dir_pkgconfig}

# qmake
ln -s  ${dir_qt5}bin/qmake /usr/local/bin/qmake

# pkgconfig files
cd ${dir_pkgconfig}
pwd
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file}
done
