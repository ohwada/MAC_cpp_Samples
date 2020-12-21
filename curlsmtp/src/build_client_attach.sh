#!/bin/bash

# 2020-07-01 K.OHWADA
# build client_attach.cpp

g++ src/client_attach.cpp src/curlsmtp.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` -o client_attach

