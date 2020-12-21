#!/bin/bash

# 2020-07-01 K.OHWADA
# build client_utf8.cpp

g++ src/client_utf8.cpp src/curlsmtp.cpp src/curlsmtp2.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` -o client_utf8

