#!/bin/bash

# create a directory structure to operate the Intermediate CA 
# 2021-02-01 K.OHWADA

 # Usage:
# cd work # your favorite directory
# bash setup_inter_ca.sh

# create a directory with the same structure as demoCA

mkdir interCA
mkdir  interCA/private/
mkdir  interCA/newcerts/
mkdir  interCA/certs/
mkdir  interCA/crl/
mkdir  interCA/csr/
touch interCA/index.txt
echo 00 > interCA/serial
echo 1000 > interCA/crlnumber
