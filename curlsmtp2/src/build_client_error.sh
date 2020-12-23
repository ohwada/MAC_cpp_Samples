#!/bin/bash

# 2020-07-01 K.OHWADA
# build client_text.cpp

g++ src/client_error.cpp src/curlsmtp.cpp src/curlsmtp2.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` `pkg-config --cflags --libs libglog`  -o client_error

