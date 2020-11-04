#!/bin/bash

# 2020-07-01 K.OHWADA
# change file arrangement

dir_vmime=/usr/local/opt/vmime
dir_include=${dir_vmime}/include
dir_lib=${dir_vmime}/lib
dir_pkgconfig=${dir_vmime}/pkgconfig
dir_usr_lib=/usr/local/lib

mkdir ${dir_vmime}
mkdir ${dir_include}
mkdir ${dir_lib}
mkdir ${dir_pkgconfig}


# mv header files
mv /usr/local/include/vmime ${dir_include}/vmime


# backup pkgconfig file
mv /usr/local/lib/pkgconfig/vmime.pc ${dir_pkgconfig}/vmime.pc.bak


# copy pkgconfig files
cd pkgconfig
pwd
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    cp  ${file} ${dir_pkgconfig}
    ln -s ${dir_pkgconfig}/${file} /usr/local/lib/pkgconfig/${file}
done

# link pkgconfig files
cd ${dir_pkgconfig}
pwd
files=`ls -1 *.pc`
for file in ${files}
do
    echo ${file}
    ln -s /usr/local/lib/pkgconfig/${file} ${dir_pkgconfig}/${file} 
done


# move library files
cd ${dir_usr_lib}
pwd
files=`ls -1 libvmime*`
for file in ${files}
do
    echo ${file}
    mv ${dir_usr_lib}/${file} ${dir_lib}/${file}
done


# link library files
cd ${dir_lib}
pwd
files=`ls -1 lib*`
for file in ${files}
do
    echo ${file}
    ln -s ${dir_lib}/${file} ${dir_usr_lib}/${file}
done