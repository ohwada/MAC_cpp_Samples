#!/bin/bash

# create a directory structure to operate the Root CA
# 2021-02-01 K.OHWADA

# Usage:
# cd work # your favorite directory
# bash setup_root_ca.sh

# the name "demoCA" is set in configuration file
# configuration file: 
Linux: /usr/lib/ssl/openssl.cnf
MAC: /usr/local/etc/openssl@1.1/openssl.cnf

mkdir  demoCA/
mkdir  demoCA/private/
mkdir  demoCA/newcerts/
mkdir demoCA/certs
mkdir demoCA/crl
touch demoCA/index.txt
echo 00 > demoCA/serial
