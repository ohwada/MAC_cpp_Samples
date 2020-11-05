#!/bin/bash

# 2020-07-01 K.OHWADA
# build code

g++ send_mail_text.cpp curlsmtp.cpp file_util.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` -o text
