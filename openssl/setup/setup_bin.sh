#!/bin/bash

# setup for bin command
# 2020-07-01 K.OHWADA

ssl_ver=1.1.1i
dir_ssl_bin=/usr/local/Cellar/openssl@1.1/${ssl_ver}/bin

 ln -s  ${dir_ssl_bin}/openssl /usr/local/bin/openssl
