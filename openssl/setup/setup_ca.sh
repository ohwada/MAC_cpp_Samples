#!/bin/bash

# setup for Certificate Authority
# 2020-07-01 K.OHWADA

# configuration file: /usr/local/etc/openssl@1.1/openssl.cnf
# defined TSA root directory

mkdir  demoCA/ # TSA root directory
mkdir  demoCA/private/
mkdir  demoCA/newcerts/
touch demoCA/index.txt
echo 00 > demoCA/serial

