#!/bin/bash

# 2020-07-01 K.OHWADA
# build client_text.cpp

g++ src/client_text.cpp src/curlsmtp.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` -o client_text

