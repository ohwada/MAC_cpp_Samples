#!/bin/bash
# 2022-06-01 K.OHWADA
# copy header files to system area

boost_url_dir=/usr/local/include/boost_url

mkdir ${boost_url_dir}

cp -r include/boost ${boost_url_dir}

