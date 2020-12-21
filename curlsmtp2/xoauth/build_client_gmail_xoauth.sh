#!/bin/bash

# 2020-07-01 K.OHWADA
# client_gmail_xoauth.cpp

g++ xoauth/client_gmail_xoauth.cpp src/curlsmtp.cpp src/curlsmtp2.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` -o client_xoauth
